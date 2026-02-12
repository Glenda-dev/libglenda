#ifndef GLENDA_CLIENT_INIT_H
#define GLENDA_CLIENT_INIT_H

#include <glenda/types.h>
#include <glenda/error.h>
#include <glenda/protocol.h>

typedef struct
{
    glenda_cap_ptr_t endpoint;
} glenda_init_client_t;

glenda_error_t init_client_init(glenda_init_client_t *client, glenda_cap_ptr_t endpoint);
glenda_error_t init_client_start_service(glenda_init_client_t *client, const char *service);
glenda_error_t init_client_stop_service(glenda_init_client_t *client, const char *service);
glenda_error_t init_client_restart_service(glenda_init_client_t *client, const char *service);
glenda_error_t init_client_reload_service(glenda_init_client_t *client, const char *service);

#endif /* GLENDA_CLIENT_INIT_H */
