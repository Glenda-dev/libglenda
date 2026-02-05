#ifndef GLENDA_ARCH_RISCV64_MEM_H
#define GLENDA_ARCH_RISCV64_MEM_H

/* RISC-V 64 SV39 specific constants */
#define PGSIZE 4096
#define VA_MAX (1UL << 38)
#define EMPTY_VA 0
#define VPN_MASK 0x1FF
#define USER_VA 0x10000
#define KSTACK_PAGES 4

/* Memory Layout */
#define TRAMPOLINE_VA (VA_MAX - PGSIZE)
#define TRAPFRAME_VA (TRAMPOLINE_VA - PGSIZE)
#define UTCB_VA (TRAPFRAME_VA - PGSIZE)
#define STACK_VA (UTCB_VA - PGSIZE)
#define ENTRY_VA USER_VA

#endif /* GLENDA_ARCH_RISCV64_MEM_H */
