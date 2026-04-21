#ifndef GLENDA_CAP_KERNEL_H
#define GLENDA_CAP_KERNEL_H

#include <glenda/cap.h>
#include <glenda/error.h>

glenda_error_t glenda_kernel_console_put_str(glenda_cap_ptr_t kernel, const char *s);
glenda_error_t glenda_kernel_console_get_char(glenda_cap_ptr_t kernel, char *out_char);
glenda_error_t glenda_kernel_console_get_str(glenda_cap_ptr_t kernel, char *buf, size_t buf_size, size_t *out_len);
glenda_error_t glenda_get_time(glenda_cap_ptr_t kernel, size_t *out);
glenda_error_t glenda_kernel_shell(glenda_cap_ptr_t kernel);
glenda_error_t glenda_kernel_get_irq(glenda_cap_ptr_t kernel, size_t irq, glenda_cap_ptr_t dest_cptr);
glenda_error_t glenda_kernel_get_mmio(glenda_cap_ptr_t kernel, size_t paddr, size_t pages, glenda_cap_ptr_t dest_cptr);
glenda_error_t glenda_kernel_set_alarm(glenda_cap_ptr_t kernel, size_t ticks, glenda_cap_ptr_t ntfn_cptr);
glenda_error_t glenda_kernel_get_freq(glenda_cap_ptr_t kernel, size_t *out_freq);
glenda_error_t glenda_kernel_system_reset(glenda_cap_ptr_t kernel, size_t reset_type);
#endif
