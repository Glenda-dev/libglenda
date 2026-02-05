.section .text.entry
.globl _start
_start:
    xor %rbp, %rbp
    
    # Align stack to 16 bytes
    and $-16, %rsp

    call glenda_start

1:
    hlt
    jmp 1b
