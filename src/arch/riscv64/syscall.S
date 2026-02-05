.section .text
.global syscall

/*
 * size_t syscall(size_t cptr, size_t method)
 * a0 = cptr
 * a1 = method
 *
 * return a0
 */
syscall:
    /* Move method (a1) to a7 */
    mv a7, a1
    ecall
    ret
