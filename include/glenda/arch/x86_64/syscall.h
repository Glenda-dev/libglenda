#ifndef GLENDA_ARCH_X86_64_SYSCALL_H
#define GLENDA_ARCH_X86_64_SYSCALL_H

#include <glenda/stddef.h>

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

static inline size_t syscall_ipc(size_t cptr, size_t method, size_t *msgtag, size_t *badge, size_t mrs[4])
{
    register size_t rax __asm__("rax") = method;
    register size_t rdi __asm__("rdi") = cptr;
    register size_t rsi __asm__("rsi") = msgtag ? *msgtag : 0;
    register size_t rdx __asm__("rdx") = badge ? *badge : 0;
    register size_t rcx __asm__("rcx") = mrs ? mrs[0] : 0;
    register size_t r8 __asm__("r8") = mrs ? mrs[1] : 0;
    register size_t r9 __asm__("r9") = mrs ? mrs[2] : 0;
    register size_t r10 __asm__("r10") = mrs ? mrs[3] : 0;

    __asm__ volatile(
        "syscall"
        : "+r"(rax), "+r"(rsi), "+r"(rdx), "+r"(rcx), "+r"(r8), "+r"(r9), "+r"(r10)
        : "r"(rdi)
        : "r11", "memory");

    if (msgtag) *msgtag = rsi;
    if (badge) *badge = rdx;
    if (mrs) {
        mrs[0] = rcx;
        mrs[1] = r8;
        mrs[2] = r9;
        mrs[3] = r10;
    }
    return rax;
}

#endif /* GLENDA_ARCH_X86_64_SYSCALL_H */
