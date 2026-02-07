#ifndef GLENDA_CLIENT_PROCESS_H
#define GLENDA_CLIENT_PROCESS_H

#include <glenda/types.h>
#include <glenda/error.h>

typedef struct
{
    glenda_cap_ptr_t endpoint;
} glenda_process_client_t;

glenda_error_t process_client_init(glenda_process_client_t *client, glenda_cap_ptr_t endpoint);
glenda_error_t process_client_exit(glenda_process_client_t *client, int code);

#endif /* GLENDA_CLIENT_PROCESS_H */
