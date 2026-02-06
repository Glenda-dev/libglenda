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

size_t sys_invoke(glenda_cap_ptr_t cptr, size_t method, size_t *args)
{
    glenda_utcb_t *utcb = get_utcb();
    if (args)
    {
        for (int i = 0; i < MAX_MRS; i++)
        {
            utcb->mrs_regs[i] = args[i];
        }
    }
    return syscall(cptr, method);
}

glenda_error_t glenda_cnode_mint(glenda_cap_ptr_t cnode, glenda_cap_ptr_t src, glenda_cap_ptr_t dest, glenda_badge_t badge, glenda_cap_rights_t rights)
{
    size_t args[MAX_MRS] = {src, dest, badge, (size_t)rights, 0, 0, 0, 0};
    return (glenda_error_t)sys_invoke(cnode, METHOD_CNODE_MINT, args);
}

glenda_error_t glenda_cnode_copy(glenda_cap_ptr_t cnode, glenda_cap_ptr_t src, glenda_cap_ptr_t dest, glenda_cap_rights_t rights)
{
    size_t args[MAX_MRS] = {src, dest, (size_t)rights, 0, 0, 0, 0, 0};
    return (glenda_error_t)sys_invoke(cnode, METHOD_CNODE_COPY, args);
}

glenda_error_t glenda_cnode_delete(glenda_cap_ptr_t cnode, glenda_cap_ptr_t slot)
{
    size_t args[MAX_MRS] = {slot, 0, 0, 0, 0, 0, 0, 0};
    return (glenda_error_t)sys_invoke(cnode, METHOD_CNODE_DELETE, args);
}

glenda_error_t glenda_cnode_revoke(glenda_cap_ptr_t cnode, glenda_cap_ptr_t slot)
{
    size_t args[MAX_MRS] = {slot, 0, 0, 0, 0, 0, 0, 0};
    return (glenda_error_t)sys_invoke(cnode, METHOD_CNODE_REVOKE, args);
}

glenda_error_t glenda_cnode_debug_print(glenda_cap_ptr_t cnode)
{
    return (glenda_error_t)sys_invoke(cnode, METHOD_CNODE_DEBUG_PRINT, NULL);
}

glenda_error_t glenda_untyped_retype(glenda_cap_ptr_t untyped, glenda_cap_type_t type, size_t size_bits, glenda_cap_ptr_t root, size_t node_index, size_t node_depth, size_t node_offset, size_t num_caps)
{
    size_t args[MAX_MRS] = {(size_t)type, size_bits, root, node_index, node_depth, node_offset, num_caps, 0};
    return (glenda_error_t)sys_invoke(untyped, METHOD_UNTYPED_RETYPE, args);
}

glenda_error_t glenda_tcb_configure(glenda_cap_ptr_t tcb, glenda_cap_ptr_t fault_handler, glenda_cap_ptr_t cspace_root, glenda_cap_ptr_t vspace_root, size_t ipc_buffer_addr, glenda_cap_ptr_t ipc_buffer_cap)
{
    size_t args[MAX_MRS] = {fault_handler, cspace_root, vspace_root, ipc_buffer_addr, ipc_buffer_cap, 0, 0, 0};
    return (glenda_error_t)sys_invoke(tcb, METHOD_TCB_CONFIGURE, args);
}

glenda_error_t glenda_tcb_set_priority(glenda_cap_ptr_t tcb, size_t priority)
{
    size_t args[MAX_MRS] = {priority, 0, 0, 0, 0, 0, 0, 0};
    return (glenda_error_t)sys_invoke(tcb, METHOD_TCB_SET_PRIORITY, args);
}

glenda_error_t glenda_tcb_set_entrypoint(glenda_cap_ptr_t tcb, size_t entrypoint, size_t stack, size_t arg)
{
    size_t args[MAX_MRS] = {entrypoint, stack, arg, 0, 0, 0, 0, 0};
    return (glenda_error_t)sys_invoke(tcb, METHOD_TCB_SET_ENTRYPOINT, args);
}

glenda_error_t glenda_tcb_resume(glenda_cap_ptr_t tcb)
{
    return (glenda_error_t)sys_invoke(tcb, METHOD_TCB_RESUME, NULL);
}

glenda_error_t glenda_tcb_suspend(glenda_cap_ptr_t tcb)
{
    return (glenda_error_t)sys_invoke(tcb, METHOD_TCB_SUSPEND, NULL);
}

glenda_error_t glenda_vspace_map(glenda_cap_ptr_t vspace, glenda_cap_ptr_t frame, size_t vaddr, glenda_cap_rights_t rights, size_t cache_policy)
{
    size_t args[MAX_MRS] = {frame, vaddr, (size_t)rights, cache_policy, 0, 0, 0, 0};
    return (glenda_error_t)sys_invoke(vspace, METHOD_VSPACE_MAP, args);
}

glenda_error_t glenda_vspace_unmap(glenda_cap_ptr_t vspace, size_t vaddr)
{
    size_t args[MAX_MRS] = {vaddr, 0, 0, 0, 0, 0, 0, 0};
    return (glenda_error_t)sys_invoke(vspace, METHOD_VSPACE_UNMAP, args);
}

glenda_error_t glenda_vspace_map_table(glenda_cap_ptr_t vspace, glenda_cap_ptr_t table, size_t vaddr)
{
    size_t args[MAX_MRS] = {table, vaddr, 0, 0, 0, 0, 0, 0};
    return (glenda_error_t)sys_invoke(vspace, METHOD_VSPACE_MAP_TABLE, args);
}

glenda_error_t glenda_endpoint_send(glenda_cap_ptr_t endpoint, glenda_msg_tag_t msg_info, size_t *args)
{
    glenda_utcb_t *utcb = get_utcb();
    utcb->msg_tag = msg_info;
    return (glenda_error_t)sys_invoke(endpoint, METHOD_IPC_SEND, args);
}

glenda_error_t glenda_endpoint_recv(glenda_cap_ptr_t endpoint, glenda_cap_ptr_t reply_slot, size_t *out_val)
{
    glenda_utcb_t *utcb = get_utcb();
    utcb->recv_window = reply_slot;
    glenda_error_t err = (glenda_error_t)sys_invoke(endpoint, METHOD_IPC_RECV, NULL);
    if (err == GLENDA_SUCCESS && out_val)
    {
        *out_val = utcb->mrs_regs[0];
    }
    return err;
}

glenda_error_t glenda_endpoint_call(glenda_cap_ptr_t endpoint, glenda_msg_tag_t msg_info, size_t *args)
{
    glenda_utcb_t *utcb = get_utcb();
    utcb->msg_tag = msg_info;
    return (glenda_error_t)sys_invoke(endpoint, METHOD_IPC_CALL, args);
}

glenda_error_t glenda_endpoint_notify(glenda_cap_ptr_t endpoint, size_t badge)
{
    size_t args[MAX_MRS] = {badge, 0, 0, 0, 0, 0, 0, 0};
    return (glenda_error_t)sys_invoke(endpoint, METHOD_IPC_NOTIFY, args);
}

glenda_error_t glenda_irq_set_notification(glenda_cap_ptr_t irq_handler, glenda_cap_ptr_t notification)
{
    size_t args[MAX_MRS] = {notification, 0, 0, 0, 0, 0, 0, 0};
    return (glenda_error_t)sys_invoke(irq_handler, METHOD_IRQ_SET_NOTIFICATION, args);
}

glenda_error_t glenda_irq_ack(glenda_cap_ptr_t irq_handler)
{
    return (glenda_error_t)sys_invoke(irq_handler, METHOD_IRQ_ACK, NULL);
}

glenda_error_t glenda_kernel_console_put_str(glenda_cap_ptr_t kernel, const char *s)
{
    glenda_utcb_t *utcb = get_utcb();
    size_t len = glenda_strlen(s);
    size_t written = utcb_write(utcb, (const uint8_t *)s, len);
    if (written == len)
    {
        return (glenda_error_t)sys_invoke(kernel, METHOD_KERNEL_CONSOLE_PUT_STR, NULL);
    }
    else
    {
        return GLENDA_ERR_BUFFER_OVERFLOW;
    }
}

glenda_error_t glenda_kernel_console_get_char(glenda_cap_ptr_t kernel, char *out_char)
{
    glenda_utcb_t *utcb = get_utcb();
    glenda_error_t err = (glenda_error_t)sys_invoke(kernel, METHOD_KERNEL_CONSOLE_GET_CHAR, NULL);
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
    glenda_error_t err = (glenda_error_t)sys_invoke(kernel, METHOD_KERNEL_CONSOLE_GET_STR, NULL);
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

glenda_error_t glenda_get_time(glenda_cap_ptr_t kernel)
{
    glenda_utcb_t *utcb = get_utcb();
    glenda_error_t err = (glenda_error_t)sys_invoke(kernel, METHOD_KERNEL_CONSOLE_GET_STR, NULL);
    return utcb->mrs_regs[0];
}
