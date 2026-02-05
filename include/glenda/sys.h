#ifndef GLENDA_SYS_H
#define GLENDA_SYS_H

#include <stddef.h>
#include <glenda/error.h>

/**
 * @brief Initialize the process environment.
 *
 * @return size_t Initial heap break point or 0 on failure.
 */
size_t glenda_sys_init(void);

/**
 * @brief Exit the process.
 *
 * @param code Exit code.
 */
void glenda_sys_exit(int code);

/**
 * @brief Change the data segment size.
 *
 * @param increment Amount to increase/decrease the heap.
 * @return void* Previous break point, or (void*)-1 on failure.
 */
void *glenda_sys_sbrk(ptrdiff_t increment);

#endif /* GLENDA_SYS_H */
