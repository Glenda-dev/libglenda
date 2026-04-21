#ifndef GLENDA_CLIENT_VOLUME_H
#define GLENDA_CLIENT_VOLUME_H

#include <glenda/types.h>
#include <glenda/error.h>
#include <glenda/protocol.h>

typedef struct
{
    glenda_cap_ptr_t endpoint;
} glenda_volume_client_t;

glenda_error_t volume_client_init(glenda_volume_client_t *client, glenda_cap_ptr_t endpoint);
glenda_error_t volume_client_get_device(glenda_volume_client_t *client, glenda_badge_t pid, glenda_cap_ptr_t recv, glenda_cap_ptr_t *out_endpoint);
glenda_error_t volume_client_get_info(glenda_volume_client_t *client, glenda_volume_info_t *out_info);

#endif
