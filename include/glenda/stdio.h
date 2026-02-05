#ifndef _STDIO_H
#define _STDIO_H

#include <glenda/types.h>
#include <glenda/stdarg.h>

/**
 * @brief Formatted print to console.
 */
int glenda_printf(const char *format, ...);

/**
 * @brief Scan formatted input from console.
 */
int glenda_scanf(const char *format, ...);

/**
 * @brief Formatted print to string.
 */
int glenda_vsnprintf(char *str, size_t size, const char *format, va_list ap);

/**
 * @brief Formatted scan from string.
 */
int glenda_vsnscanf(const char *str, const char *format, va_list ap);

#define scanf(...) glenda_scanf(__VA_ARGS__)
#define printf(...) glenda_printf(__VA_ARGS__)

#endif /* _STDIO_H */