#include <glenda/utils.h>

size_t glenda_strlen(const char *s)
{
    const char *p = s;
    while (*p)
        p++;
    return p - s;
}

void *glenda_memset(void *s, int c, size_t n)
{
    unsigned char *p = s;
    while (n--)
        *p++ = (unsigned char)c;
    return s;
}

void *glenda_memcpy(void *dest, const void *src, size_t n)
{
    unsigned char *d = dest;
    const unsigned char *s = src;
    while (n--)
        *d++ = *s++;
    return dest;
}
