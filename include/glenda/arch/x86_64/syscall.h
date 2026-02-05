#ifndef GLENDA_ARCH_X86_64_SYSCALL_H
#define GLENDA_ARCH_X86_64_SYSCALL_H

#include <stddef.h>

static inline size_t syscall(size_t cptr, size_t method)
{
    register size_t rax __asm__("rax") = method;
    register size_t rdi __asm__("rdi") = cptr;

    __asm__ volatile(
        "syscall"
        : "+r"(rax)
        : "r"(rdi)
        : "rcx", "r11", "memory");

    return rax;
}

#endif /* GLENDA_ARCH_X86_64_SYSCALL_H */
