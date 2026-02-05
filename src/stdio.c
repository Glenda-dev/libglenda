#include <glenda/console.h>
#include <stdarg.h>

// Extern declarations for musl functions
extern int vsnprintf(char *s, size_t n, const char *format, va_list arg);
extern int vsscanf(const char *s, const char *format, va_list arg);

int glenda_vsnprintf(char *str, size_t size, const char *format, va_list ap)
{
    return vsnprintf(str, size, format, ap);
}

int glenda_vsnscanf(const char *str, const char *format, va_list ap)
{
    // Musl uses vsscanf for string-based scanning
    return vsscanf(str, format, ap);
}
