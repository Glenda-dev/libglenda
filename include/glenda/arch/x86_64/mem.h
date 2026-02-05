#ifndef GLENDA_ARCH_X86_64_MEM_H
#define GLENDA_ARCH_X86_64_MEM_H

/* x86_64 specific constants (Example values) */
#define PGSIZE 4096
#define VA_MAX 0x00007FFFFFFFF000UL
#define EMPTY_VA 0
#define USER_VA 0x400000
#define KSTACK_PAGES 4

/* Memory Layout */
#define TRAMPOLINE_VA (VA_MAX - PGSIZE)
#define TRAPFRAME_VA (TRAMPOLINE_VA - PGSIZE)
#define UTCB_VA (TRAPFRAME_VA - PGSIZE)
#define STACK_VA (UTCB_VA - PGSIZE)
#define ENTRY_VA USER_VA

#endif /* GLENDA_ARCH_X86_64_MEM_H */
