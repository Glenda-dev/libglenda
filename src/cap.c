#include <glenda/ipc.h>
#include <glenda/syscall.h>
#include <glenda/method.h>
#include <glenda/cap/cnode.h>
#include <glenda/cap/tcb.h>
#include <glenda/cap/untyped.h>
#include <glenda/cap/vspace.h>
#include <glenda/cap/endpoint.h>
#include <glenda/cap/irq.h>
#include <glenda/cap/kernel.h>
#include <glenda/utils.h>

size_t sys_invoke(glenda_cap_ptr_t cptr, size_t method)
{
    return syscall(cptr, method);
}

glenda_error_t glenda_cnode_mint(glenda_cap_ptr_t cnode, glenda_cap_ptr_t src, glenda_cap_ptr_t dest, glenda_badge_t badge, glenda_cap_rights_t rights)
{
    glenda_utcb_t *utcb = get_utcb();
    utcb->mrs_regs[0] = src;
    utcb->mrs_regs[1] = dest;
    utcb->mrs_regs[2] = badge;
    utcb->mrs_regs[3] = (size_t)rights;
    return (glenda_error_t)sys_invoke(cnode, METHOD_CNODE_MINT);
}

glenda_error_t glenda_cnode_copy(glenda_cap_ptr_t cnode, glenda_cap_ptr_t src, glenda_cap_ptr_t dest, glenda_cap_rights_t rights)
{
    glenda_utcb_t *utcb = get_utcb();
    utcb->mrs_regs[0] = src;
    utcb->mrs_regs[1] = dest;
    utcb->mrs_regs[2] = (size_t)rights;
    return (glenda_error_t)sys_invoke(cnode, METHOD_CNODE_COPY);
}

glenda_error_t glenda_cnode_delete(glenda_cap_ptr_t cnode, glenda_cap_ptr_t slot)
{
    glenda_utcb_t *utcb = get_utcb();
    utcb->mrs_regs[0] = slot;
    return (glenda_error_t)sys_invoke(cnode, METHOD_CNODE_DELETE);
}

glenda_error_t glenda_cnode_revoke(glenda_cap_ptr_t cnode, glenda_cap_ptr_t slot)
{
    glenda_utcb_t *utcb = get_utcb();
    utcb->mrs_regs[0] = slot;
    return (glenda_error_t)sys_invoke(cnode, METHOD_CNODE_REVOKE);
}

glenda_error_t glenda_cnode_debug_print(glenda_cap_ptr_t cnode)
{
    return (glenda_error_t)sys_invoke(cnode, METHOD_CNODE_DEBUG_PRINT);
}

glenda_error_t glenda_untyped_retype(glenda_cap_ptr_t untyped, glenda_cap_type_t type, size_t size_bits, glenda_cap_ptr_t root, size_t node_index, size_t node_depth, size_t node_offset, size_t num_caps)
{
    glenda_utcb_t *utcb = get_utcb();
    utcb->mrs_regs[0] = (size_t)type;
    utcb->mrs_regs[1] = size_bits;
    utcb->mrs_regs[2] = root;
    utcb->mrs_regs[3] = node_index;
    utcb->mrs_regs[4] = node_depth;
    utcb->mrs_regs[5] = node_offset;
    utcb->mrs_regs[6] = num_caps;
    return (glenda_error_t)sys_invoke(untyped, METHOD_UNTYPED_RETYPE);
}

glenda_error_t glenda_tcb_configure(glenda_cap_ptr_t tcb, glenda_cap_ptr_t fault_handler, glenda_cap_ptr_t cspace_root, glenda_cap_ptr_t vspace_root, size_t ipc_buffer_addr, glenda_cap_ptr_t ipc_buffer_cap)
{
    glenda_utcb_t *utcb = get_utcb();
    utcb->mrs_regs[0] = fault_handler;
    utcb->mrs_regs[1] = cspace_root;
    utcb->mrs_regs[2] = vspace_root;
    utcb->mrs_regs[3] = ipc_buffer_addr;
    utcb->mrs_regs[4] = ipc_buffer_cap;
    return (glenda_error_t)sys_invoke(tcb, METHOD_TCB_CONFIGURE);
}

glenda_error_t glenda_tcb_set_priority(glenda_cap_ptr_t tcb, size_t priority)
{
    glenda_utcb_t *utcb = get_utcb();
    utcb->mrs_regs[0] = priority;
    return (glenda_error_t)sys_invoke(tcb, METHOD_TCB_SET_PRIORITY);
}

glenda_error_t glenda_tcb_set_entrypoint(glenda_cap_ptr_t tcb, size_t entrypoint, size_t stack, size_t arg)
{
    glenda_utcb_t *utcb = get_utcb();
    utcb->mrs_regs[0] = entrypoint;
    utcb->mrs_regs[1] = stack;
    utcb->mrs_regs[2] = arg;
    return (glenda_error_t)sys_invoke(tcb, METHOD_TCB_SET_ENTRYPOINT);
}

glenda_error_t glenda_tcb_resume(glenda_cap_ptr_t tcb)
{
    return (glenda_error_t)sys_invoke(tcb, METHOD_TCB_RESUME);
}

glenda_error_t glenda_tcb_suspend(glenda_cap_ptr_t tcb)
{
    return (glenda_error_t)sys_invoke(tcb, METHOD_TCB_SUSPEND);
}

glenda_error_t glenda_vspace_map(glenda_cap_ptr_t vspace, glenda_cap_ptr_t frame, size_t vaddr, glenda_cap_rights_t rights, size_t cache_policy)
{
    glenda_utcb_t *utcb = get_utcb();
    utcb->mrs_regs[0] = frame;
    utcb->mrs_regs[1] = vaddr;
    utcb->mrs_regs[2] = (size_t)rights;
    utcb->mrs_regs[3] = cache_policy;
    return (glenda_error_t)sys_invoke(vspace, METHOD_VSPACE_MAP);
}

glenda_error_t glenda_vspace_unmap(glenda_cap_ptr_t vspace, size_t vaddr)
{
    glenda_utcb_t *utcb = get_utcb();
    utcb->mrs_regs[0] = vaddr;
    return (glenda_error_t)sys_invoke(vspace, METHOD_VSPACE_UNMAP);
}

glenda_error_t glenda_vspace_map_table(glenda_cap_ptr_t vspace, glenda_cap_ptr_t table, size_t vaddr)
{
    glenda_utcb_t *utcb = get_utcb();
    utcb->mrs_regs[0] = table;
    utcb->mrs_regs[1] = vaddr;
    return (glenda_error_t)sys_invoke(vspace, METHOD_VSPACE_MAP_TABLE);
}

glenda_error_t glenda_endpoint_send(glenda_cap_ptr_t endpoint)
{
    return (glenda_error_t)sys_invoke(endpoint, METHOD_IPC_SEND);
}

glenda_error_t glenda_endpoint_recv(glenda_cap_ptr_t endpoint)
{
    return (glenda_error_t)sys_invoke(endpoint, METHOD_IPC_RECV);
}

glenda_error_t glenda_endpoint_call(glenda_cap_ptr_t endpoint)
{
    return (glenda_error_t)sys_invoke(endpoint, METHOD_IPC_CALL);
}

glenda_error_t glenda_endpoint_notify(glenda_cap_ptr_t endpoint)
{
    return (glenda_error_t)sys_invoke(endpoint, METHOD_IPC_NOTIFY);
}

glenda_error_t glenda_endpoint_proxy(glenda_cap_ptr_t endpoint)
{
    return (glenda_error_t)sys_invoke(endpoint, METHOD_IPC_NOTIFY);
}

glenda_error_t glenda_reply(glenda_cap_ptr_t reply)
{
    return (glenda_error_t)sys_invoke(reply, METHOD_REPLY);
}

glenda_error_t glenda_irq_set_notification(glenda_cap_ptr_t irq_handler, glenda_cap_ptr_t notification)
{
    glenda_utcb_t *utcb = get_utcb();
    utcb->mrs_regs[0] = notification;
    return (glenda_error_t)sys_invoke(irq_handler, METHOD_IRQ_SET_NOTIFICATION);
}

glenda_error_t glenda_irq_ack(glenda_cap_ptr_t irq_handler)
{
    return (glenda_error_t)sys_invoke(irq_handler, METHOD_IRQ_ACK);
}

glenda_error_t glenda_kernel_console_put_str(glenda_cap_ptr_t kernel, const char *s)
{
    glenda_utcb_t *utcb = get_utcb();
    size_t len = glenda_strlen(s);
    size_t written = utcb_write(utcb, (const uint8_t *)s, len);
    if (written == len)
    {
        return (glenda_error_t)sys_invoke(kernel, METHOD_KERNEL_CONSOLE_PUT_STR);
    }
    else
    {
        return GLENDA_ERR_BUFFER_OVERFLOW;
    }
}

glenda_error_t glenda_kernel_console_get_char(glenda_cap_ptr_t kernel, char *out_char)
{
    glenda_utcb_t *utcb = get_utcb();
    glenda_error_t err = (glenda_error_t)sys_invoke(kernel, METHOD_KERNEL_CONSOLE_GET_CHAR);
    if (err == GLENDA_SUCCESS && out_char)
    {
        uint8_t c;
        if (utcb_read(utcb, &c, 1) == 1)
        {
            *out_char = (char)c;
        }
        else
        {
            return GLENDA_ERR_IO;
        }
    }
    return err;
}

glenda_error_t glenda_kernel_console_get_str(glenda_cap_ptr_t kernel, char *buf, size_t buf_size, size_t *out_len)
{
    glenda_utcb_t *utcb = get_utcb();
    utcb_clear(utcb);
    glenda_error_t err = (glenda_error_t)sys_invoke(kernel, METHOD_KERNEL_CONSOLE_GET_STR);
    if (err == GLENDA_SUCCESS)
    {
        size_t len = utcb->mrs_regs[0];
        if (len > buf_size - 1)
        {
            len = buf_size - 1;
        }
        if (out_len)
        {
            *out_len = len;
        }

        utcb_read(utcb, (uint8_t *)buf, len);
        buf[len] = '\0';
    }
    return err;
}

glenda_error_t glenda_get_time(glenda_cap_ptr_t kernel, size_t *out)
{
    glenda_utcb_t *utcb = get_utcb();
    glenda_error_t err = (glenda_error_t)sys_invoke(kernel, METHOD_KERNEL_GET_TIME);
    if (err == GLENDA_SUCCESS && out)
    {
        *out = utcb->mrs_regs[0];
    }
    return err;
}
