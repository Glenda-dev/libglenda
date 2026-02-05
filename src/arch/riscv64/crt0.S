.section .text.entry
.globl _start
_start:
    .option push
    .option norelax
    la gp, __global_pointer$
    .option pop

    # Set up stack pointer if not set by loader (usually set by kernel/loader)
    # But for safety, we assume it's already set.
    
    # Set frame pointer to zero
    li s0, 0

    # Jump to C initialization function
    call glenda_start

    # If glenda_start returns, loop forever
1:
    ebreak
    j 1b
