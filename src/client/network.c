#include <glenda/client/network.h>
#include <glenda/cap/endpoint.h>
#include <glenda/ipc.h>
#include <glenda/utils.h>

glenda_error_t network_client_init(glenda_network_client_t *client, glenda_cap_ptr_t endpoint)
{
    if (!client)
        return GLENDA_ERR_INVALID_PARAM;
    client->endpoint = endpoint;
    return GLENDA_SUCCESS;
}

glenda_error_t network_client_socket(glenda_network_client_t *client, int domain, int type, int protocol, size_t *out_socket)
{
    glenda_utcb_t *utcb = get_utcb();
    utcb_clear(utcb);
    utcb->mrs_regs[0] = domain;
    utcb->mrs_regs[1] = type;
    utcb->mrs_regs[2] = protocol;
    utcb->msg_tag = msg_tag_new(PROTO_NETWORK, NETWORK_SOCKET, MSG_FLAG_NONE);
    glenda_error_t err = glenda_endpoint_call(client->endpoint);
    if (err == GLENDA_SUCCESS && out_socket)
    {
        *out_socket = utcb->mrs_regs[0];
    }
    return err;
}

glenda_error_t network_client_bind(glenda_network_client_t *client, const void *addr, size_t addrlen)
{
    glenda_utcb_t *utcb = get_utcb();
    utcb_clear(utcb);
    utcb_write(utcb, (const uint8_t *)addr, addrlen);
    utcb->msg_tag = msg_tag_new(PROTO_NETWORK, NETWORK_BIND, MSG_FLAG_NONE);
    return glenda_endpoint_call(client->endpoint);
}

glenda_error_t network_client_listen(glenda_network_client_t *client, int backlog)
{
    glenda_utcb_t *utcb = get_utcb();
    utcb_clear(utcb);
    utcb->mrs_regs[0] = backlog;
    utcb->msg_tag = msg_tag_new(PROTO_NETWORK, NETWORK_LISTEN, MSG_FLAG_NONE);
    return glenda_endpoint_call(client->endpoint);
}

glenda_error_t network_client_accept(glenda_network_client_t *client, size_t *out_socket)
{
    glenda_utcb_t *utcb = get_utcb();
    utcb_clear(utcb);
    utcb->msg_tag = msg_tag_new(PROTO_NETWORK, NETWORK_ACCEPT, MSG_FLAG_NONE);
    glenda_error_t err = glenda_endpoint_call(client->endpoint);
    if (err == GLENDA_SUCCESS && out_socket)
    {
        *out_socket = utcb->mrs_regs[0];
    }
    return err;
}

glenda_error_t network_client_connect(glenda_network_client_t *client, const void *addr, size_t addrlen)
{
    glenda_utcb_t *utcb = get_utcb();
    utcb_clear(utcb);
    utcb_write(utcb, (const uint8_t *)addr, addrlen);
    utcb->msg_tag = msg_tag_new(PROTO_NETWORK, NETWORK_CONNECT, MSG_FLAG_NONE);
    return glenda_endpoint_call(client->endpoint);
}

glenda_error_t network_client_send(glenda_network_client_t *client, const void *buf, size_t len, int flags, size_t *out_sent)
{
    glenda_utcb_t *utcb = get_utcb();
    utcb_clear(utcb);
    size_t to_write = (len < IPC_BUFFER_SIZE) ? len : IPC_BUFFER_SIZE;
    utcb_write(utcb, (const uint8_t *)buf, to_write);
    utcb->mrs_regs[0] = to_write;
    utcb->mrs_regs[1] = flags;
    utcb->msg_tag = msg_tag_new(PROTO_NETWORK, NETWORK_SEND, MSG_FLAG_NONE);
    glenda_error_t err = glenda_endpoint_call(client->endpoint);
    if (err == GLENDA_SUCCESS && out_sent)
    {
        *out_sent = utcb->mrs_regs[0];
    }
    return err;
}

glenda_error_t network_client_recv(glenda_network_client_t *client, void *buf, size_t len, int flags, size_t *out_received)
{
    glenda_utcb_t *utcb = get_utcb();
    utcb_clear(utcb);
    utcb->mrs_regs[0] = len;
    utcb->mrs_regs[1] = flags;
    utcb->msg_tag = msg_tag_new(PROTO_NETWORK, NETWORK_RECV, MSG_FLAG_NONE);
    glenda_error_t err = glenda_endpoint_call(client->endpoint);
    if (err == GLENDA_SUCCESS)
    {
        size_t received = utcb->mrs_regs[0];
        if (received > len)
            received = len;
        glenda_memcpy(buf, utcb->ipc_buffer, received);
        if (out_received)
            *out_received = received;
    }
    return err;
}

glenda_error_t network_client_close(glenda_network_client_t *client)
{
    glenda_utcb_t *utcb = get_utcb();
    utcb_clear(utcb);
    utcb->msg_tag = msg_tag_new(PROTO_NETWORK, NETWORK_CLOSE, MSG_FLAG_NONE);
    return glenda_endpoint_call(client->endpoint);
}
