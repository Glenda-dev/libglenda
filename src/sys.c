#include <glenda/sys.h>
#include <glenda/syscall.h>
#include <glenda/ipc.h>
#include <glenda/protocol.h>
#include <glenda/cap/endpoint.h>
#include <glenda/console.h>

size_t glenda_sys_init(void)
{
#ifndef GLENDA_SERVICE
    glenda_msg_tag_t tag = msg_tag_new(PROTO_RESOURCE, RESOURCE_GETCAP, 0);
    glenda_utcb_t *utcb = get_utcb();
    utcb->mrs_regs[0] = INIT_CAP_CONSOLE;
    utcb->recv_window = CAP_KERNEL;
    utcb->msg_tag = tag;
    glenda_error_t err = glenda_endpoint_call(CAP_MON);
    if (err != GLENDA_SUCCESS)
    {
        return utcb->mrs_regs[0];
    }
#endif
    glenda_console_init(CAP_KERNEL);
    return 0;
}

size_t sys_invoke_ipc(glenda_cap_ptr_t cptr, size_t method, glenda_utcb_t *utcb)
{
    size_t msgtag = utcb->msg_tag.raw;
    size_t badge = utcb->badge;
    size_t mrs[4] = {
        utcb->mrs_regs[0],
        utcb->mrs_regs[1],
        utcb->mrs_regs[2],
        utcb->mrs_regs[3],
    };
    size_t ret = syscall_ipc(cptr, method, &msgtag, &badge, mrs);
    utcb->msg_tag.raw = msgtag;
    utcb->badge = badge;
    utcb->mrs_regs[0] = mrs[0];
    utcb->mrs_regs[1] = mrs[1];
    utcb->mrs_regs[2] = mrs[2];
    utcb->mrs_regs[3] = mrs[3];
    return ret;
}

void glenda_sys_exit(int code)
{
#ifndef GLENDA_BAREMETAL
    glenda_msg_tag_t tag = msg_tag_new(PROTO_PROCESS, PROC_EXIT, 0);
    glenda_utcb_t *utcb = get_utcb();
    utcb->mrs_regs[0] = (size_t)code;
    for (int i = 1; i < MAX_MRS; i++)
        utcb->mrs_regs[i] = 0;
    utcb->msg_tag = tag;
    glenda_endpoint_send(CAP_MON);
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
    glenda_msg_tag_t tag = msg_tag_new(PROTO_RESOURCE, RESOURCE_SBRK, 0);
    glenda_utcb_t *utcb = get_utcb();
    utcb->mrs_regs[0] = (size_t)increment;
    for (int i = 1; i < MAX_MRS; i++)
        utcb->mrs_regs[i] = 0;
    utcb->msg_tag = tag;
    glenda_error_t err = glenda_endpoint_call(CAP_MON);
    if (err == GLENDA_SUCCESS)
    {
        size_t old_brk = utcb->mrs_regs[0];
        if (old_brk != 0)
        {
            return (void *)old_brk;
        }
    }
#endif
    return (void *)-1;
}
