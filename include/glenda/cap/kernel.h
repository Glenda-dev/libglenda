#ifndef GLENDA_CAP_KERNEL_H
#define GLENDA_CAP_KERNEL_H

#include <glenda/cap.h>
#include <glenda/error.h>

glenda_error_t glenda_kernel_console_put_str(glenda_cap_ptr_t kernel, const char *s);
glenda_error_t glenda_kernel_console_get_char(glenda_cap_ptr_t kernel, char *out_char);
glenda_error_t glenda_kernel_console_get_str(glenda_cap_ptr_t kernel, char *buf, size_t buf_size, size_t *out_len);
glenda_error_t glenda_get_time(glenda_cap_ptr_t kernel, size_t *out);
#endif
