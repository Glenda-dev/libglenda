#include <glenda/ipc.h>
#include <glenda/syscall.h>

long sys_invoke(CapPtr cptr, size_t method, size_t *args) {
    UTCB *utcb = get_utcb();
    if (args) {
        for (int i = 0; i < MAX_MRS; i++) {
            utcb->mrs_regs[i] = args[i];
        }
    }
    return (long)syscall(cptr, method);
}
