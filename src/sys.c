#include <glenda/sys.h>
#include <glenda/ipc.h>
#include <glenda/protocol.h>
#include <glenda/cap/endpoint.h>

size_t glenda_sys_init(void)
{
#ifndef GLENDA_BAREMETAL
    glenda_msg_tag_t tag = msg_tag_new(PROTO_PROCESS, PROC_INIT, 0);
    size_t args[MAX_MRS] = {0};
    glenda_error_t err = glenda_endpoint_call(CAP_MON, tag, args);
    if (err == GLENDA_SUCCESS)
    {
        return get_utcb()->mrs_regs[0];
    }
#endif
    return 0;
}

void glenda_sys_exit(int code)
{
#ifndef GLENDA_BAREMETAL
    glenda_msg_tag_t tag = msg_tag_new(PROTO_PROCESS, PROC_EXIT, 0);
    size_t args[MAX_MRS] = {(size_t)code, 0, 0, 0, 0, 0, 0, 0};
    glenda_endpoint_send(CAP_MON, tag, args);
#endif
    while (1)
    {
#if defined(GLENDA_ARCH_RISCV64)
        __asm__ volatile("ebreak");
#elif defined(GLENDA_ARCH_X86_64)
        __asm__ volatile("hlt");
#endif
    }
}

void *glenda_sys_sbrk(ptrdiff_t increment)
{
#ifndef GLENDA_BAREMETAL
    glenda_msg_tag_t tag = msg_tag_new(PROTO_PROCESS, PROC_SBRK, 0);
    size_t args[MAX_MRS] = {(size_t)increment, 0, 0, 0, 0, 0, 0, 0};
    glenda_error_t err = glenda_endpoint_call(CAP_MON, tag, args);
    if (err == GLENDA_SUCCESS)
    {
        size_t old_brk = get_utcb()->mrs_regs[0];
        if (old_brk != 0)
        {
            return (void *)old_brk;
        }
    }
#endif
    return (void *)-1;
}
