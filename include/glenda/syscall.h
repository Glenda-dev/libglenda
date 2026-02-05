#ifndef GLENDA_SYSCALL_H
#define GLENDA_SYSCALL_H

#include <stddef.h>
#include <glenda/cap.h>

// Low logic raw syscall
size_t syscall(size_t cptr, size_t method);

// Helper to invoke a capability
long sys_invoke(CapPtr cptr, size_t method, size_t *args);

#endif
