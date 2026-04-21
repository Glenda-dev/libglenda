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

static inline size_t syscall_ipc(size_t cptr, size_t method, size_t *msgtag, size_t *badge, size_t mrs[4])
{
    register size_t a0 __asm__("a0") = cptr;
    register size_t a1 __asm__("a1") = msgtag ? *msgtag : 0;
    register size_t a2 __asm__("a2") = badge ? *badge : 0;
    register size_t a3 __asm__("a3") = mrs ? mrs[0] : 0;
    register size_t a4 __asm__("a4") = mrs ? mrs[1] : 0;
    register size_t a5 __asm__("a5") = mrs ? mrs[2] : 0;
    register size_t a6 __asm__("a6") = mrs ? mrs[3] : 0;
    register size_t a7 __asm__("a7") = method;

    __asm__ volatile(
        "ecall"
        : "+r"(a0), "+r"(a1), "+r"(a2), "+r"(a3), "+r"(a4), "+r"(a5), "+r"(a6)
        : "r"(a7)
        : "memory");

    if (msgtag) *msgtag = a1;
    if (badge) *badge = a2;
    if (mrs) {
        mrs[0] = a3;
        mrs[1] = a4;
        mrs[2] = a5;
        mrs[3] = a6;
    }
    return a0;
}

#endif /* GLENDA_ARCH_RISCV64_SYSCALL_H */
