#ifndef GLENDA_CONSOLE_H
#define GLENDA_CONSOLE_H

#include <glenda/types.h>
#include <glenda/stdarg.h>

/**
 * @brief Initialize the console system.
 */
void glenda_console_init(glenda_cap_ptr_t kernel_cap);

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

/**
 * @brief Get a string from console.
 */
char *glenda_gets(char *s, int size);
