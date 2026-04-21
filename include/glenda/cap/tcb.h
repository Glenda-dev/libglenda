#ifndef GLENDA_CAP_TCB_H
#define GLENDA_CAP_TCB_H

#include <glenda/cap.h>
#include <glenda/error.h>

glenda_error_t glenda_tcb_configure(glenda_cap_ptr_t tcb, glenda_cap_ptr_t fault_handler, glenda_cap_ptr_t cspace_root, glenda_cap_ptr_t vspace_root, size_t ipc_buffer_addr, glenda_cap_ptr_t ipc_buffer_cap);
glenda_error_t glenda_tcb_set_priority(glenda_cap_ptr_t tcb, size_t priority);
glenda_error_t glenda_tcb_set_entrypoint(glenda_cap_ptr_t tcb, size_t entrypoint, size_t stack, size_t arg);
glenda_error_t glenda_tcb_set_address(glenda_cap_ptr_t tcb, size_t utcb_va, size_t trapframe_va);
glenda_error_t glenda_tcb_set_fault_handler(glenda_cap_ptr_t tcb, glenda_cap_ptr_t fault_handler);
glenda_error_t glenda_tcb_set_registers(glenda_cap_ptr_t tcb, const size_t *regs, size_t count);
glenda_error_t glenda_tcb_yield(glenda_cap_ptr_t tcb);
glenda_error_t glenda_tcb_set_timeslice(glenda_cap_ptr_t tcb, size_t timeslice_ms);
glenda_error_t glenda_tcb_fork_from(glenda_cap_ptr_t tcb, glenda_cap_ptr_t parent);
glenda_error_t glenda_tcb_deliver_upcall(glenda_cap_ptr_t tcb, size_t handler, size_t arg0, size_t arg1, size_t arg2, size_t arg3);
glenda_error_t glenda_tcb_resume(glenda_cap_ptr_t tcb);
glenda_error_t glenda_tcb_suspend(glenda_cap_ptr_t tcb);

#endif
