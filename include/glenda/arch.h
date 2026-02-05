#ifndef GLENDA_ARCH_H
#define GLENDA_ARCH_H

#if defined(__riscv) && (__riscv_xlen == 64)
#define GLENDA_ARCH_RISCV64
#elif defined(__x86_64__)
#define GLENDA_ARCH_X86_64
#else
#error "Unsupported architecture"
#endif

#endif /* GLENDA_ARCH_H */
