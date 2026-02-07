#include <glenda/console.h>
#include <glenda/stdarg.h>
#include <glenda/stddef.h>
#include <glenda/stdbool.h>
#include <glenda/stdio.h>
#include <glenda/client/fs.h>
#include <glenda/cap.h>

#define MAX_FILES 16
static FILE file_pool[MAX_FILES];
static bool file_used[MAX_FILES];

FILE _stdin = {.cap = 0, .offset = 0};
FILE _stdout = {.cap = 0, .offset = 0};
FILE _stderr = {.cap = 0, .offset = 0};

FILE *glenda_stdin = &_stdin;
FILE *glenda_stdout = &_stdout;
FILE *glenda_stderr = &_stderr;

#ifndef GLENDA_BAREMETAL
FILE *glenda_fopen(const char *path, const char *mode)
{
    int i;
    for (i = 0; i < MAX_FILES; i++)
    {
        if (!file_used[i])
            break;
    }
    if (i == MAX_FILES)
        return NULL;

    uint32_t flags = 0;
    if (mode[0] == 'r')
        flags = O_RDONLY;
    else if (mode[0] == 'w')
        flags = O_WRONLY | O_CREAT | O_TRUNC;
    else if (mode[0] == 'a')
        flags = O_WRONLY | O_CREAT | O_APPEND;

    glenda_fs_client_t client;
    fs_client_init(&client, CAP_MON); // Use root FS/Monitor endpoint for open

    glenda_cap_ptr_t file_cap;
    if (fs_client_open(&client, path, flags, 0644, &file_cap) != GLENDA_SUCCESS)
    {
        return NULL;
    }

    file_used[i] = true;
    file_pool[i].cap = file_cap;
    file_pool[i].offset = 0;
    file_pool[i].eof = false;
    file_pool[i].error = false;
    return &file_pool[i];
}

int glenda_fclose(FILE *stream)
{
    if (!stream)
        return -1;

    glenda_fs_client_t client;
    fs_client_init(&client, stream->cap);
    fs_client_close(&client);

    // Find in pool to mark unused
    for (int i = 0; i < MAX_FILES; i++)
    {
        if (&file_pool[i] == stream)
        {
            file_used[i] = false;
            break;
        }
    }
    return 0;
}

size_t glenda_fread(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    if (!stream || !ptr)
        return 0;

    glenda_fs_client_t client;
    fs_client_init(&client, stream->cap);

    size_t total_read = 0;
    size_t to_read = size * nmemb;

    if (fs_client_read(&client, stream->offset, ptr, to_read, &total_read) == GLENDA_SUCCESS)
    {
        stream->offset += total_read;
        if (total_read < to_read)
            stream->eof = true;
        return total_read / size;
    }

    stream->error = true;
    return 0;
}
#else
FILE *glenda_fopen(const char *path, const char *mode) { return NULL; }
int glenda_fclose(FILE *stream) { return -1; }
size_t glenda_fread(void *ptr, size_t size, size_t nmemb, FILE *stream) { return 0; }
#endif

static void glenda_putc(char c)
{
    char buf[2] = {c, 0};
#ifdef GLENDA_BAREMETAL
    glenda_kernel_console_put_str(CAP_KERNEL, buf);
#else
    glenda_puts(buf);
#endif
}

size_t glenda_fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    if (!stream || !ptr)
        return 0;

    if (stream == glenda_stdout || stream == glenda_stderr)
    {
        // Special case for console
        size_t total = size * nmemb;
        const char *s = (const char *)ptr;

#ifdef GLENDA_BAREMETAL
        // Direct kernel console output
        char buf[2] = {0, 0};
        for (size_t i = 0; i < total; i++)
        {
            buf[0] = s[i];
            glenda_kernel_console_put_str(CAP_KERNEL, buf);
        }
#else
        // Using console service abstraction
        for (size_t i = 0; i < total; i++)
        {
            glenda_putc(s[i]);
        }
#endif
        return nmemb;
    }

#ifndef GLENDA_BAREMETAL
    glenda_fs_client_t client;
    fs_client_init(&client, stream->cap);

    size_t total_written = 0;
    size_t to_write = size * nmemb;

    if (fs_client_write(&client, stream->offset, ptr, to_write, &total_written) == GLENDA_SUCCESS)
    {
        stream->offset += total_written;
        return total_written / size;
    }

    stream->error = true;
#endif
    return 0;
}

#ifndef GLENDA_BAREMETAL
int glenda_fseek(FILE *stream, long offset, int whence)
{
    if (!stream)
        return -1;

    glenda_fs_client_t client;
    fs_client_init(&client, stream->cap);

    uint64_t new_offset;
    if (fs_client_seek(&client, offset, whence, &new_offset) == GLENDA_SUCCESS)
    {
        stream->offset = new_offset;
        stream->eof = false;
        return 0;
    }
    return -1;
}

long glenda_ftell(FILE *stream)
{
    return stream ? (long)stream->offset : -1;
}

void glenda_rewind(FILE *stream)
{
    glenda_fseek(stream, 0, 0); // SEEK_SET
}
#else
int glenda_fseek(FILE *stream, long offset, int whence) { return -1; }
long glenda_ftell(FILE *stream) { return -1; }
void glenda_rewind(FILE *stream) {}
#endif

// ----------------------------------------------------------------------------
// Internal Helpers
// ----------------------------------------------------------------------------

static bool is_digit(char c)
{
    return c >= '0' && c <= '9';
}

static bool is_space(char c)
{
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

static void append(char *str, size_t size, size_t *pos, char c)
{
    if (*pos < size - 1)
    {
        str[*pos] = c;
    }
    (*pos)++;
}

static void append_str(char *str, size_t size, size_t *pos, const char *s)
{
    while (*s)
    {
        append(str, size, pos, *s++);
    }
}

static void append_int(char *str, size_t size, size_t *pos, long long value, int base, int width, char pad, bool upper)
{
    char buf[64];
    int len = 0;
    unsigned long long uval = (unsigned long long)value;
    bool negative = false;

    if (base == 10 && value < 0)
    {
        negative = true;
        uval = (unsigned long long)(-value);
    }

    // Convert to string reversed
    do
    {
        int arr = uval % base;
        buf[len++] = (arr < 10) ? ('0' + arr) : ((upper ? 'A' : 'a') + arr - 10);
        uval /= base;
    } while (uval > 0);

    if (negative)
    {
        width--; // Consume one width for sign
    }

    // Padding (right aligned)
    while (width > len)
    {
        append(str, size, pos, pad);
        width--;
    }

    if (negative)
    {
        append(str, size, pos, '-');
    }

    // Output number
    while (len > 0)
    {
        append(str, size, pos, buf[--len]);
    }
}

// ----------------------------------------------------------------------------
// glenda_vsnprintf
// ----------------------------------------------------------------------------

int glenda_vsnprintf(char *str, size_t size, const char *format, va_list ap)
{
    size_t pos = 0;

    // Ensure we can at least write null char if size > 0
    if (size > 0 && str)
    {
        str[0] = '\0';
    }

    for (const char *p = format; *p; p++)
    {
        if (*p != '%')
        {
            append(str, size, &pos, *p);
            continue;
        }

        p++; // Skip '%'

        // Width & Padding
        char pad = ' ';
        int width = 0;
        if (*p == '0')
        {
            pad = '0';
            p++;
        }
        while (is_digit(*p))
        {
            width = width * 10 + (*p - '0');
            p++;
        }

        switch (*p)
        {
        case 's':
        {
            const char *s = va_arg(ap, const char *);
            if (!s)
                s = "(null)";
            append_str(str, size, &pos, s);
            break;
        }
        case 'd': // int
            append_int(str, size, &pos, va_arg(ap, int), 10, width, pad, false);
            break;
        case 'u': // unsigned
            append_int(str, size, &pos, va_arg(ap, unsigned int), 10, width, pad, false);
            break;
        case 'x': // hex
            append_int(str, size, &pos, va_arg(ap, unsigned int), 16, width, pad, false);
            break;
        case 'X': // HEX
            append_int(str, size, &pos, va_arg(ap, unsigned int), 16, width, pad, true);
            break;
        case 'p': // pointer
            append_str(str, size, &pos, "0x");
            append_int(str, size, &pos, (long long)va_arg(ap, void *), 16, 0, '0', false);
            break;
        case 'c': // char
            append(str, size, &pos, (char)va_arg(ap, int));
            break;
        case '%':
            append(str, size, &pos, '%');
            break;
        default:
            append(str, size, &pos, '%');
            append(str, size, &pos, *p);
            break;
        }
    }

    if (size > 0 && str)
    {
        if (pos < size)
            str[pos] = '\0';
        else
            str[size - 1] = '\0';
    }

    return (int)pos;
}

// ----------------------------------------------------------------------------
// glenda_vsnscanf
// ----------------------------------------------------------------------------

int glenda_vsnscanf(const char *str, const char *format, va_list ap)
{
    const char *s = str;
    const char *p = format;
    int items = 0;

    while (*p && *s)
    {
        // Skip whitespace in format matches any whitespace in input
        if (is_space(*p))
        {
            while (is_space(*p))
                p++;
            while (is_space(*s))
                s++;
            continue;
        }

        if (*p != '%')
        {
            if (*s == *p)
            {
                s++;
                p++;
            }
            else
            {
                return items; // Mismatch
            }
            continue;
        }

        p++; // Skip '%'

        // Simple format specifiers
        switch (*p)
        {
        case 'd':
        {
            while (is_space(*s))
                s++; // skip leading space
            int *v = va_arg(ap, int *);
            long n = 0;
            int sign = 1;
            if (*s == '-')
            {
                s++;
                sign = -1;
            }
            else if (*s == '+')
            {
                s++;
            }

            if (!is_digit(*s))
                return items;

            while (is_digit(*s))
            {
                n = n * 10 + (*s - '0');
                s++;
            }
            *v = (int)(n * sign);
            items++;
            break;
        }
        case 's':
        {
            while (is_space(*s))
                s++;
            char *buf = va_arg(ap, char *);
            if (!*s)
                return items;
            while (*s && !is_space(*s))
            {
                *buf++ = *s++;
            }
            *buf = '\0';
            items++;
            break;
        }
        case 'c':
        {
            char *c = va_arg(ap, char *);
            *c = *s++;
            items++;
            break;
        }
        default:
            return items;
        }
        p++;
    }

    return items;
}

int glenda_printf(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    int ret = glenda_vfprintf(glenda_stdout, format, ap);
    va_end(ap);
    return ret;
}

int glenda_fprintf(FILE *stream, const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    int ret = glenda_vfprintf(stream, format, ap);
    va_end(ap);
    return ret;
}

int glenda_vfprintf(FILE *stream, const char *format, va_list ap)
{
    char buf[1024];
    int ret = glenda_vsnprintf(buf, sizeof(buf), format, ap);
    if (ret > 0)
    {
        glenda_fwrite(buf, 1, (size_t)ret, stream);
    }
    return ret;
}

int glenda_scanf(const char *format, ...)
{
    char buf[1024]; // Buffer for console line input
    va_list ap;
    int items;

    // Read a full line from console first (works in both baremetal and app mode)
    if (!glenda_gets(buf, sizeof(buf)))
    {
        return 0;
    }

    va_start(ap, format);
    items = glenda_vsnscanf(buf, format, ap);
    va_end(ap);

    return items;
}
