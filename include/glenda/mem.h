#ifndef GLENDA_MEM_H
#define GLENDA_MEM_H

#include <stddef.h>

#if defined(__riscv) && (__riscv_xlen == 64)
#include <glenda/arch/riscv64/mem.h>
#elif defined(__x86_64__)
#include <glenda/arch/x86_64/mem.h>
#else
#error "Unsupported architecture"
#endif

/* Generic Memory Layout Constants */
#define BOOTINFO_VA 0x40000000UL
#define INITRD_VA 0x50000000UL
#define HEAP_VA 0x20000000UL

/* Memory Permissions (PTE Flags compat) */
typedef enum
{
    PERM_READ = (1 << 1),
    PERM_WRITE = (1 << 2),
    PERM_EXECUTE = (1 << 3),
    PERM_USER = (1 << 4),
} glenda_perm_t;

#endif /* GLENDA_MEM_H */
