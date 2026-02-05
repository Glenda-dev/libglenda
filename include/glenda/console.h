#ifndef GLENDA_CONSOLE_H
#define GLENDA_CONSOLE_H

#include <glenda/types.h>
#include <stdarg.h>

/**
 * @brief Initialize the console system.
 */
void glenda_console_init(glenda_cap_ptr_t kernel_cap);

/**
 * @brief Formatted print to console.
 */
int glenda_printf(const char *format, ...);

/**
 * @brief Formatted scan from console.
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

/**
 * @brief Print a string to console.
 */
void glenda_puts(const char *s);

/**
 * @brief Get a character from console.
 */
char glenda_getchar(void);

/**
 * @brief Vfprintf-like function for internal use.
 */
int glenda_vprintf(const char *format, va_list ap);

#endif /* GLENDA_CONSOLE_H */
