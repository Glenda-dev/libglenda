#include <glenda/client/generic.h>
#include <glenda/cap/endpoint.h>
#include <glenda/ipc.h>
#include <glenda/utils.h>

glenda_error_t generic_client_init(glenda_generic_client_t *client, glenda_cap_ptr_t endpoint)
{
    if (!client)
        return GLENDA_ERR_INVALID_PARAM;
    client->endpoint = endpoint;
    return GLENDA_SUCCESS;
}

glenda_error_t generic_client_ping(glenda_generic_client_t *client, size_t value, size_t *out_value)
{
    glenda_utcb_t *utcb = get_utcb();
    utcb_clear(utcb);
    utcb->mrs_regs[0] = value;
    utcb->msg_tag = msg_tag_new(PROTO_GENERIC, GENERIC_PING, MSG_FLAG_NONE);
    glenda_error_t err = glenda_endpoint_call(client->endpoint);
    if (err == GLENDA_SUCCESS && out_value)
    {
        *out_value = utcb->mrs_regs[0];
    }
    return err;
}

glenda_error_t generic_client_share_memory(glenda_generic_client_t *client, glenda_cap_ptr_t cap)
{
    glenda_utcb_t *utcb = get_utcb();
    utcb_clear(utcb);
    utcb->cap_transfer = cap;
    utcb->msg_tag = msg_tag_new(PROTO_GENERIC, GENERIC_SHARE_MEMORY, MSG_FLAG_HAS_CAP);
    return glenda_endpoint_call(client->endpoint);
}

glenda_error_t generic_client_send_message(glenda_generic_client_t *client, const char *message)
{
    glenda_utcb_t *utcb = get_utcb();
    utcb_clear(utcb);
    size_t len = glenda_strlen(message);
    utcb_write(utcb, (const uint8_t *)message, len);
    utcb->msg_tag = msg_tag_new(PROTO_GENERIC, GENERIC_SEND_MESSAGE, MSG_FLAG_HAS_BUFFER);
    return glenda_endpoint_call(client->endpoint);
}
