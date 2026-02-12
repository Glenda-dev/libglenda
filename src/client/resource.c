#include <glenda/client/resource.h>
#include <glenda/cap/endpoint.h>
#include <glenda/ipc.h>
#include <glenda/utils.h>

glenda_error_t resource_client_init(glenda_resource_client_t *client, glenda_cap_ptr_t endpoint)
{
    if (!client)
        return GLENDA_ERR_INVALID_PARAM;
    client->endpoint = endpoint;
    return GLENDA_SUCCESS;
}

glenda_error_t resource_client_alloc(glenda_resource_client_t *client, glenda_badge_t pid, glenda_cap_type_t obj_type, size_t flags, glenda_cap_ptr_t recv)
{
    glenda_utcb_t *utcb = get_utcb();
    utcb_clear(utcb);
    utcb->mrs_regs[0] = obj_type;
    utcb->mrs_regs[1] = flags;
    utcb->recv_window = recv;
    utcb->msg_tag = msg_tag_new(PROTO_RESOURCE, RESOURCE_ALLOC, MSG_FLAG_NONE);
    return glenda_endpoint_call(client->endpoint);
}

glenda_error_t resource_client_dma_alloc(glenda_resource_client_t *client, glenda_badge_t pid, size_t pages, glenda_cap_ptr_t recv, uintptr_t *out_paddr)
{
    glenda_utcb_t *utcb = get_utcb();
    utcb_clear(utcb);
    utcb->mrs_regs[0] = pages;
    utcb->recv_window = recv;
    utcb->msg_tag = msg_tag_new(PROTO_RESOURCE, RESOURCE_DMA_ALLOC, MSG_FLAG_NONE);
    glenda_error_t err = glenda_endpoint_call(client->endpoint);
    if (err == GLENDA_SUCCESS && out_paddr)
    {
        *out_paddr = utcb->mrs_regs[0];
    }
    return err;
}

glenda_error_t resource_client_free(glenda_resource_client_t *client, glenda_badge_t pid, glenda_cap_ptr_t cap)
{
    glenda_utcb_t *utcb = get_utcb();
    utcb_clear(utcb);
    utcb->mrs_regs[0] = cap;
    utcb->msg_tag = msg_tag_new(PROTO_RESOURCE, RESOURCE_FREE, MSG_FLAG_NONE);
    return glenda_endpoint_call(client->endpoint);
}

glenda_error_t resource_client_get_cap(glenda_resource_client_t *client, glenda_badge_t pid, glenda_resource_type_t type, size_t id, glenda_cap_ptr_t recv)
{
    glenda_utcb_t *utcb = get_utcb();
    utcb_clear(utcb);
    utcb->mrs_regs[0] = type;
    utcb->mrs_regs[1] = id;
    utcb->recv_window = recv;
    utcb->msg_tag = msg_tag_new(PROTO_RESOURCE, RESOURCE_GETCAP, MSG_FLAG_NONE);
    return glenda_endpoint_call(client->endpoint);
}

glenda_error_t resource_client_register_cap(glenda_resource_client_t *client, glenda_badge_t pid, glenda_resource_type_t type, size_t id, glenda_cap_ptr_t cap)
{
    glenda_utcb_t *utcb = get_utcb();
    utcb_clear(utcb);
    utcb->mrs_regs[0] = type;
    utcb->mrs_regs[1] = id;
    utcb->cap_transfer = cap;
    utcb->msg_tag = msg_tag_new(PROTO_RESOURCE, RESOURCE_REGISTER_CAP, MSG_FLAG_HAS_CAP);
    return glenda_endpoint_call(client->endpoint);
}

glenda_error_t resource_client_get_config(glenda_resource_client_t *client, glenda_badge_t pid, const char *name, glenda_cap_ptr_t recv, size_t *out_size)
{
    glenda_utcb_t *utcb = get_utcb();
    utcb_clear(utcb);
    size_t name_len = glenda_strlen(name);
    utcb_write(utcb, (const uint8_t *)name, name_len);
    utcb->recv_window = recv;
    utcb->msg_tag = msg_tag_new(PROTO_RESOURCE, RESOURCE_GET_CONFIG, MSG_FLAG_HAS_BUFFER);
    glenda_error_t err = glenda_endpoint_call(client->endpoint);
    if (err == GLENDA_SUCCESS && out_size)
    {
        *out_size = utcb->mrs_regs[0];
    }
    return err;
}

glenda_error_t resource_client_brk(glenda_resource_client_t *client, glenda_badge_t pid, intptr_t increment, size_t *out_new_brk)
{
    glenda_utcb_t *utcb = get_utcb();
    utcb_clear(utcb);
    utcb->mrs_regs[0] = (size_t)increment;
    utcb->msg_tag = msg_tag_new(PROTO_RESOURCE, RESOURCE_SBRK, MSG_FLAG_NONE);
    glenda_error_t err = glenda_endpoint_call(client->endpoint);
    if (err == GLENDA_SUCCESS && out_new_brk)
    {
        *out_new_brk = utcb->mrs_regs[0];
    }
    return err;
}

glenda_error_t resource_client_mmap(glenda_resource_client_t *client, glenda_badge_t pid, glenda_cap_ptr_t frame, uintptr_t addr, size_t len, uintptr_t *out_addr)
{
    glenda_utcb_t *utcb = get_utcb();
    utcb_clear(utcb);
    utcb->cap_transfer = frame;
    utcb->mrs_regs[0] = frame;
    utcb->mrs_regs[1] = addr;
    utcb->mrs_regs[2] = len;
    utcb->msg_tag = msg_tag_new(PROTO_RESOURCE, RESOURCE_MMAP, MSG_FLAG_HAS_CAP);
    glenda_error_t err = glenda_endpoint_call(client->endpoint);
    if (err == GLENDA_SUCCESS && out_addr)
    {
        *out_addr = utcb->mrs_regs[0];
    }
    return err;
}

glenda_error_t resource_client_munmap(glenda_resource_client_t *client, glenda_badge_t pid, uintptr_t addr, size_t len)
{
    glenda_utcb_t *utcb = get_utcb();
    utcb_clear(utcb);
    utcb->mrs_regs[0] = addr;
    utcb->mrs_regs[1] = len;
    utcb->msg_tag = msg_tag_new(PROTO_RESOURCE, RESOURCE_MUNMAP, MSG_FLAG_NONE);
    return glenda_endpoint_call(client->endpoint);
}
