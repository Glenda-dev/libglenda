#include <glenda/console.h>
#include <glenda/stdarg.h>
#include <glenda/stddef.h>
#include <glenda/stdbool.h>

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
    char buf[1024];
    va_list ap;
    va_start(ap, format);
    int ret = glenda_vsnprintf(buf, sizeof(buf), format, ap);
    va_end(ap);
    glenda_puts(buf);
    return ret;
}
int glenda_scanf(const char *format, ...)
{
    char buf[1024]; // Buffer for console line input
    va_list ap;
    int items;

    // Read a full line from console first
    if (!glenda_gets(buf, sizeof(buf)))
    {
        return 0;
    }

    va_start(ap, format);
    items = glenda_vsnscanf(buf, format, ap);
    va_end(ap);

    return items;
}
