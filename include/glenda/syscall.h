#ifndef GLENDA_SYSCALL_H
#define GLENDA_SYSCALL_H

#include <glenda/arch.h>
#include <glenda/cap.h>

#if defined(GLENDA_ARCH_RISCV64)
#include <glenda/arch/riscv64/syscall.h>
#elif defined(GLENDA_ARCH_X86_64)
#include <glenda/arch/x86_64/syscall.h>
#endif

// Helper to invoke a capability
size_t sys_invoke(glenda_cap_ptr_t cptr, size_t method);

#endif
