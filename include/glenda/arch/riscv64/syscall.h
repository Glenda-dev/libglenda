#ifndef GLENDA_ARCH_RISCV64_SYSCALL_H
#define GLENDA_ARCH_RISCV64_SYSCALL_H

#include <glenda/stddef.h>

static inline size_t syscall(size_t cptr, size_t method)
{
    register size_t a0 __asm__("a0") = cptr;
    register size_t a7 __asm__("a7") = method;

    __asm__ volatile(
        "ecall"
        : "+r"(a0)
        : "r"(a7)
        : "memory");

    return a0;
}

#endif /* GLENDA_ARCH_RISCV64_SYSCALL_H */
