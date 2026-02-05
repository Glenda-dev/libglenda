#ifndef GLENDA_UTILS_H
#define GLENDA_UTILS_H

#include <glenda/stddef.h>

size_t glenda_strlen(const char *s);
void *glenda_memset(void *s, int c, size_t n);
void *glenda_memcpy(void *dest, const void *src, size_t n);

#endif /* GLENDA_UTILS_H */
