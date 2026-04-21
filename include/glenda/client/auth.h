#ifndef GLENDA_CLIENT_AUTH_H
#define GLENDA_CLIENT_AUTH_H

#include <glenda/types.h>
#include <glenda/error.h>
#include <glenda/protocol.h>

typedef struct
{
    glenda_cap_ptr_t endpoint;
} glenda_auth_client_t;

glenda_error_t auth_client_init(glenda_auth_client_t *client, glenda_cap_ptr_t endpoint);
glenda_error_t auth_client_negotiate(glenda_auth_client_t *client, uint16_t major, uint16_t minor, uint32_t flags, uint16_t *out_major, uint16_t *out_minor, uint32_t *out_flags);
glenda_error_t auth_client_get_identity(glenda_auth_client_t *client, size_t subject, glenda_identity_info_t *out_identity);
glenda_error_t auth_client_set_identity(glenda_auth_client_t *client, size_t subject, glenda_identity_info_t identity);
glenda_error_t auth_client_check_permission(glenda_auth_client_t *client, size_t subject, const char *resource, const char *operation, glenda_permission_decision_t *out_decision);
glenda_error_t auth_client_upsert_policy(glenda_auth_client_t *client, glenda_policy_rule_t policy, const char *resource, const char *operation);
glenda_error_t auth_client_delete_policy(glenda_auth_client_t *client, size_t subject, const char *resource, const char *operation);
glenda_error_t auth_client_set_policy_backend(glenda_auth_client_t *client, glenda_cap_ptr_t backend);
glenda_error_t auth_client_clear_policy_backend(glenda_auth_client_t *client);
glenda_error_t auth_client_get_policy_backend_status(glenda_auth_client_t *client, glenda_policy_backend_status_t *out_status);
glenda_error_t auth_client_get_ticket(glenda_auth_client_t *client, const char *service, void *ticket, size_t ticket_size, size_t *out_size);
glenda_error_t auth_client_validate_ticket(glenda_auth_client_t *client, const void *ticket, size_t ticket_size, int *out_valid);
glenda_error_t auth_client_logout(glenda_auth_client_t *client);
glenda_error_t auth_client_rpc(glenda_auth_client_t *client, const void *data, size_t size, void *out_data, size_t out_size, size_t *out_written);
glenda_error_t auth_client_proxy_call(glenda_auth_client_t *client, size_t target_cap, size_t label, size_t proto, const void *payload, size_t payload_size, void *out_data, size_t out_size, size_t *out_written);

#endif
