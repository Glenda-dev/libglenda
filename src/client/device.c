#include <glenda/client/device.h>
#include <glenda/cap/endpoint.h>
#include <glenda/ipc.h>
#include <glenda/utils.h>

glenda_error_t device_client_init(glenda_device_client_t *client, glenda_cap_ptr_t endpoint)
{
    if (!client)
        return GLENDA_ERR_INVALID_PARAM;
    client->endpoint = endpoint;
    return GLENDA_SUCCESS;
}

glenda_error_t device_client_get_desc(glenda_device_client_t *client, glenda_cap_ptr_t recv)
{
    glenda_utcb_t *utcb = get_utcb();
    utcb_clear(utcb);
    utcb->recv_window = recv;
    utcb->msg_tag = msg_tag_new(PROTO_DEVICE, DEVICE_GET_DESC, MSG_FLAG_NONE);
    return glenda_endpoint_call(client->endpoint);
}

glenda_error_t device_client_get_mmio(glenda_device_client_t *client, size_t index, glenda_cap_ptr_t recv)
{
    glenda_utcb_t *utcb = get_utcb();
    utcb_clear(utcb);
    utcb->mrs_regs[0] = index;
    utcb->recv_window = recv;
    utcb->msg_tag = msg_tag_new(PROTO_DEVICE, DEVICE_GET_MMIO, MSG_FLAG_NONE);
    return glenda_endpoint_call(client->endpoint);
}

glenda_error_t device_client_get_irq(glenda_device_client_t *client, size_t index, glenda_cap_ptr_t recv)
{
    glenda_utcb_t *utcb = get_utcb();
    utcb_clear(utcb);
    utcb->mrs_regs[0] = index;
    utcb->recv_window = recv;
    utcb->msg_tag = msg_tag_new(PROTO_DEVICE, DEVICE_GET_IRQ, MSG_FLAG_NONE);
    return glenda_endpoint_call(client->endpoint);
}
