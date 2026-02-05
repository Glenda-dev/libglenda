#include <glenda/console.h>
#include <glenda/cap/kernel.h>
#include <glenda/cap/endpoint.h>
#include <glenda/utils.h>

static glenda_cap_ptr_t global_kernel_cap = 0;

void glenda_console_init(glenda_cap_ptr_t kernel_cap)
{
    global_kernel_cap = kernel_cap;
}

void glenda_puts(const char *s)
{
    glenda_kernel_console_put_str(global_kernel_cap, s);
}

char glenda_getchar(void)
{
    char c = 0;
    while (glenda_kernel_console_get_char(global_kernel_cap, &c) != GLENDA_SUCCESS)
        ;
    return c;
}

// Minimal printf implementation using a local buffer
// In a real environment, we would use a more robust formatter or link with a minimal libc provider
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

// Minimal scanf implementation
// Note: This is very basic and block-interacts with the console char-by-char
int glenda_scanf(const char *format, ...)
{
    char buf[1024];
    int i = 0;
    char c;

    // Read a line (simplistic)
    while (i < (int)sizeof(buf) - 1)
    {
        c = glenda_getchar();
        if (c == '\n' || c == '\r')
        {
            glenda_puts("\n");
            break;
        }
        // Echo
        char echo[2] = {c, 0};
        glenda_puts(echo);
        buf[i++] = c;
    }
    buf[i] = '\0';

    va_list ap;
    va_start(ap, format);
    int ret = glenda_vsnscanf(buf, format, ap);
    va_end(ap);

    return ret;
}
