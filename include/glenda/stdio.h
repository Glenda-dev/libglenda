#ifndef _STDIO_H
#define _STDIO_H

#include <glenda/types.h>
#include <glenda/stdarg.h>

typedef struct
{
    glenda_cap_ptr_t cap;
    uint64_t offset;
    bool eof;
    bool error;
} GLENDA_FILE;

#define FILE GLENDA_FILE

extern FILE *glenda_stdin;
extern FILE *glenda_stdout;
extern FILE *glenda_stderr;

#define stdin glenda_stdin
#define stdout glenda_stdout
#define stderr glenda_stderr

FILE *glenda_fopen(const char *path, const char *mode);
int glenda_fclose(FILE *stream);
size_t glenda_fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
size_t glenda_fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
int glenda_fseek(FILE *stream, long offset, int whence);
long glenda_ftell(FILE *stream);
void glenda_rewind(FILE *stream);

#define fopen glenda_fopen
#define fclose glenda_fclose
#define fread glenda_fread
#define fwrite glenda_fwrite
#define fseek glenda_fseek
#define ftell glenda_ftell
#define rewind glenda_rewind

/**
 * @brief Formatted print to console.
 */
int glenda_printf(const char *format, ...);

/**
 * @brief Formatted print to stream.
 */
int glenda_fprintf(FILE *stream, const char *format, ...);
int glenda_vfprintf(FILE *stream, const char *format, va_list ap);

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

#define fprintf glenda_fprintf
#define vfprintf glenda_vfprintf
#define scanf(...) glenda_scanf(__VA_ARGS__)
#define printf(...) glenda_printf(__VA_ARGS__)

#endif /* _STDIO_H */