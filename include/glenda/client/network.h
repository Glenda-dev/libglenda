#ifndef GLENDA_CLIENT_NETWORK_H
#define GLENDA_CLIENT_NETWORK_H

#include <glenda/types.h>
#include <glenda/error.h>
#include <glenda/protocol.h>

typedef struct
{
    glenda_cap_ptr_t endpoint;
} glenda_network_client_t;

glenda_error_t network_client_init(glenda_network_client_t *client, glenda_cap_ptr_t endpoint);
glenda_error_t network_client_socket(glenda_network_client_t *client, int domain, int type, int protocol, size_t *out_socket);
glenda_error_t network_client_bind(glenda_network_client_t *client, const void *addr, size_t addrlen);
glenda_error_t network_client_listen(glenda_network_client_t *client, int backlog);
glenda_error_t network_client_accept(glenda_network_client_t *client, size_t *out_socket);
glenda_error_t network_client_connect(glenda_network_client_t *client, const void *addr, size_t addrlen);
glenda_error_t network_client_send(glenda_network_client_t *client, const void *buf, size_t len, int flags, size_t *out_sent);
glenda_error_t network_client_recv(glenda_network_client_t *client, void *buf, size_t len, int flags, size_t *out_received);
glenda_error_t network_client_close(glenda_network_client_t *client);

#endif /* GLENDA_CLIENT_NETWORK_H */
