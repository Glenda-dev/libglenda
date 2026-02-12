#ifndef GLENDA_CLIENT_GENERIC_H
#define GLENDA_CLIENT_GENERIC_H

#include <glenda/types.h>
#include <glenda/error.h>
#include <glenda/protocol.h>

typedef struct
{
    glenda_cap_ptr_t endpoint;
} glenda_generic_client_t;

glenda_error_t generic_client_init(glenda_generic_client_t *client, glenda_cap_ptr_t endpoint);
glenda_error_t generic_client_ping(glenda_generic_client_t *client, size_t value, size_t *out_value);
glenda_error_t generic_client_share_memory(glenda_generic_client_t *client, glenda_cap_ptr_t cap);
glenda_error_t generic_client_send_message(glenda_generic_client_t *client, const char *message);

#endif /* GLENDA_CLIENT_GENERIC_H */
