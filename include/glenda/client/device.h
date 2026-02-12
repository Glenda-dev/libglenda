#ifndef GLENDA_CLIENT_DEVICE_H
#define GLENDA_CLIENT_DEVICE_H

#include <glenda/types.h>
#include <glenda/error.h>
#include <glenda/protocol.h>

typedef struct
{
    glenda_cap_ptr_t endpoint;
} glenda_device_client_t;

glenda_error_t device_client_init(glenda_device_client_t *client, glenda_cap_ptr_t endpoint);
glenda_error_t device_client_get_desc(glenda_device_client_t *client, glenda_cap_ptr_t recv);
glenda_error_t device_client_get_mmio(glenda_device_client_t *client, size_t index, glenda_cap_ptr_t recv);
glenda_error_t device_client_get_irq(glenda_device_client_t *client, size_t index, glenda_cap_ptr_t recv);

#endif /* GLENDA_CLIENT_DEVICE_H */
