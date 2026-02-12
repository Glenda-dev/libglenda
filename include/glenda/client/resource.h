#ifndef GLENDA_CLIENT_RESOURCE_H
#define GLENDA_CLIENT_RESOURCE_H

#include <glenda/types.h>
#include <glenda/error.h>
#include <glenda/protocol.h>
#include <glenda/cap.h>

typedef struct
{
    glenda_cap_ptr_t endpoint;
} glenda_resource_client_t;

glenda_error_t resource_client_init(glenda_resource_client_t *client, glenda_cap_ptr_t endpoint);
glenda_error_t resource_client_alloc(glenda_resource_client_t *client, glenda_badge_t pid, glenda_cap_type_t obj_type, size_t flags, glenda_cap_ptr_t recv);
glenda_error_t resource_client_dma_alloc(glenda_resource_client_t *client, glenda_badge_t pid, size_t pages, glenda_cap_ptr_t recv, uintptr_t *out_paddr);
glenda_error_t resource_client_free(glenda_resource_client_t *client, glenda_badge_t pid, glenda_cap_ptr_t cap);
glenda_error_t resource_client_get_cap(glenda_resource_client_t *client, glenda_badge_t pid, glenda_resource_type_t type, size_t id, glenda_cap_ptr_t recv);
glenda_error_t resource_client_register_cap(glenda_resource_client_t *client, glenda_badge_t pid, glenda_resource_type_t type, size_t id, glenda_cap_ptr_t cap);
glenda_error_t resource_client_get_config(glenda_resource_client_t *client, glenda_badge_t pid, const char *name, glenda_cap_ptr_t recv, size_t *out_size);
glenda_error_t resource_client_brk(glenda_resource_client_t *client, glenda_badge_t pid, intptr_t increment, size_t *out_new_brk);
glenda_error_t resource_client_mmap(glenda_resource_client_t *client, glenda_badge_t pid, glenda_cap_ptr_t frame, uintptr_t addr, size_t len, uintptr_t *out_addr);
glenda_error_t resource_client_munmap(glenda_resource_client_t *client, glenda_badge_t pid, uintptr_t addr, size_t len);

#endif /* GLENDA_CLIENT_RESOURCE_H */
