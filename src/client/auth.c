#include <glenda/client/auth.h>
#include <glenda/cap/endpoint.h>
#include <glenda/ipc.h>
#include <glenda/utils.h>

glenda_error_t auth_client_init(glenda_auth_client_t *client, glenda_cap_ptr_t endpoint)
{
    if (!client) return GLENDA_ERR_INVALID_PARAM;
    client->endpoint = endpoint;
    return GLENDA_SUCCESS;
}

glenda_error_t auth_client_negotiate(glenda_auth_client_t *client, uint16_t major, uint16_t minor, uint32_t flags, uint16_t *out_major, uint16_t *out_minor, uint32_t *out_flags)
{
    if (!client || !out_major || !out_minor || !out_flags) return GLENDA_ERR_INVALID_PARAM;
    glenda_utcb_t *u = get_utcb(); utcb_clear(u);
    u->mrs_regs[0] = ((size_t)major << 16) | minor;
    u->mrs_regs[1] = flags;
    u->msg_tag = msg_tag_new(PROTO_AUTH, AUTH_NEGOTIATE, MSG_FLAG_NONE);
    glenda_error_t err = glenda_endpoint_call(client->endpoint);
    if (err == GLENDA_SUCCESS) { size_t p = u->mrs_regs[0]; *out_major = (p >> 16) & 0xffff; *out_minor = p & 0xffff; *out_flags = (uint32_t)u->mrs_regs[1]; }
    return err;
}

glenda_error_t auth_client_get_identity(glenda_auth_client_t *client, size_t subject, glenda_identity_info_t *out_identity)
{
    if (!client || !out_identity) return GLENDA_ERR_INVALID_PARAM;
    glenda_utcb_t *u = get_utcb(); utcb_clear(u); u->mrs_regs[0] = subject; u->msg_tag = msg_tag_new(PROTO_AUTH, AUTH_GET_IDENTITY, MSG_FLAG_NONE);
    glenda_error_t err = glenda_endpoint_call(client->endpoint);
    if (err == GLENDA_SUCCESS) *out_identity = *(glenda_identity_info_t *)&u->ipc_buffer[0];
    return err;
}

glenda_error_t auth_client_set_identity(glenda_auth_client_t *client, size_t subject, glenda_identity_info_t identity)
{
    if (!client) return GLENDA_ERR_INVALID_PARAM;
    glenda_utcb_t *u = get_utcb(); utcb_clear(u); u->mrs_regs[0] = subject; glenda_memcpy(u->ipc_buffer, &identity, sizeof(identity)); u->size = sizeof(identity); u->msg_tag = msg_tag_new(PROTO_AUTH, AUTH_SET_IDENTITY, MSG_FLAG_HAS_BUFFER); return glenda_endpoint_call(client->endpoint);
}

glenda_error_t auth_client_check_permission(glenda_auth_client_t *client, size_t subject, const char *resource, const char *operation, glenda_permission_decision_t *out_decision)
{
    if (!client || !resource || !operation || !out_decision) return GLENDA_ERR_INVALID_PARAM;
    glenda_utcb_t *u = get_utcb(); utcb_clear(u); u->mrs_regs[0] = subject; utcb_write(u, (const uint8_t *)resource, glenda_strlen(resource)); utcb_append(u, (const uint8_t *)"", 1); utcb_append(u, (const uint8_t *)operation, glenda_strlen(operation)); u->msg_tag = msg_tag_new(PROTO_AUTH, AUTH_CHECK_PERMISSION, MSG_FLAG_HAS_BUFFER); glenda_error_t err = glenda_endpoint_call(client->endpoint); if (err == GLENDA_SUCCESS) *out_decision = *(glenda_permission_decision_t *)&u->ipc_buffer[0]; return err;
}

glenda_error_t auth_client_upsert_policy(glenda_auth_client_t *client, glenda_policy_rule_t policy, const char *resource, const char *operation)
{
    if (!client || !resource || !operation) return GLENDA_ERR_INVALID_PARAM;
    glenda_utcb_t *u = get_utcb(); utcb_clear(u); u->mrs_regs[0] = policy.subject; u->mrs_regs[1] = policy.effect; u->mrs_regs[2] = policy.ttl_ms; glenda_memcpy(u->ipc_buffer, &policy, sizeof(policy)); u->size = sizeof(policy); utcb_append(u, (const uint8_t *)resource, glenda_strlen(resource)); utcb_append(u, (const uint8_t *)"", 1); utcb_append(u, (const uint8_t *)operation, glenda_strlen(operation)); u->msg_tag = msg_tag_new(PROTO_AUTH, AUTH_UPSERT_POLICY, MSG_FLAG_HAS_BUFFER); return glenda_endpoint_call(client->endpoint);
}

glenda_error_t auth_client_delete_policy(glenda_auth_client_t *client, size_t subject, const char *resource, const char *operation)
{
    if (!client || !resource || !operation) return GLENDA_ERR_INVALID_PARAM;
    glenda_utcb_t *u = get_utcb(); utcb_clear(u); u->mrs_regs[0] = subject; utcb_write(u, (const uint8_t *)resource, glenda_strlen(resource)); utcb_append(u, (const uint8_t *)"", 1); utcb_append(u, (const uint8_t *)operation, glenda_strlen(operation)); u->msg_tag = msg_tag_new(PROTO_AUTH, AUTH_DELETE_POLICY, MSG_FLAG_HAS_BUFFER); return glenda_endpoint_call(client->endpoint);
}

glenda_error_t auth_client_set_policy_backend(glenda_auth_client_t *client, glenda_cap_ptr_t backend)
{
    if (!client) return GLENDA_ERR_INVALID_PARAM;
    glenda_utcb_t *u = get_utcb(); utcb_clear(u); u->cap_transfer = backend; u->recv_window = backend; u->msg_tag = msg_tag_new(PROTO_AUTH, AUTH_SET_POLICY_BACKEND, MSG_FLAG_HAS_CAP); return glenda_endpoint_call(client->endpoint);
}

glenda_error_t auth_client_clear_policy_backend(glenda_auth_client_t *client)
{
    if (!client) return GLENDA_ERR_INVALID_PARAM;
    glenda_utcb_t *u = get_utcb(); utcb_clear(u); u->msg_tag = msg_tag_new(PROTO_AUTH, AUTH_CLEAR_POLICY_BACKEND, MSG_FLAG_NONE); return glenda_endpoint_call(client->endpoint);
}

glenda_error_t auth_client_get_policy_backend_status(glenda_auth_client_t *client, glenda_policy_backend_status_t *out_status)
{
    if (!client || !out_status) return GLENDA_ERR_INVALID_PARAM;
    glenda_utcb_t *u = get_utcb(); utcb_clear(u); u->msg_tag = msg_tag_new(PROTO_AUTH, AUTH_GET_POLICY_BACKEND_STATUS, MSG_FLAG_NONE); glenda_error_t err = glenda_endpoint_call(client->endpoint); if (err == GLENDA_SUCCESS) *out_status = *(glenda_policy_backend_status_t *)&u->ipc_buffer[0]; return err;
}

glenda_error_t auth_client_get_ticket(glenda_auth_client_t *client, const char *service, void *ticket, size_t ticket_size, size_t *out_size)
{
    if (!client || !service || !ticket || !out_size) return GLENDA_ERR_INVALID_PARAM;
    glenda_utcb_t *u = get_utcb(); utcb_clear(u); utcb_write(u, (const uint8_t *)service, glenda_strlen(service)); u->msg_tag = msg_tag_new(PROTO_AUTH, AUTH_GET_TICKET, MSG_FLAG_HAS_BUFFER); glenda_error_t err = glenda_endpoint_call(client->endpoint); if (err == GLENDA_SUCCESS) { size_t n = u->size < ticket_size ? u->size : ticket_size; glenda_memcpy(ticket, u->ipc_buffer, n); *out_size = n; } return err;
}

glenda_error_t auth_client_validate_ticket(glenda_auth_client_t *client, const void *ticket, size_t ticket_size, int *out_valid)
{
    if (!client || !ticket || !out_valid) return GLENDA_ERR_INVALID_PARAM;
    glenda_utcb_t *u = get_utcb(); utcb_clear(u); utcb_write(u, (const uint8_t *)ticket, ticket_size); u->msg_tag = msg_tag_new(PROTO_AUTH, AUTH_VALIDATE_TICKET, MSG_FLAG_HAS_BUFFER); glenda_error_t err = glenda_endpoint_call(client->endpoint); if (err == GLENDA_SUCCESS) *out_valid = u->mrs_regs[0] != 0; return err;
}

glenda_error_t auth_client_logout(glenda_auth_client_t *client)
{
    if (!client) return GLENDA_ERR_INVALID_PARAM;
    glenda_utcb_t *u = get_utcb(); utcb_clear(u); u->msg_tag = msg_tag_new(PROTO_AUTH, AUTH_LOGOUT, MSG_FLAG_NONE); return glenda_endpoint_call(client->endpoint);
}

glenda_error_t auth_client_rpc(glenda_auth_client_t *client, const void *data, size_t size, void *out_data, size_t out_size, size_t *out_written)
{
    if (!client || !data || !out_data || !out_written) return GLENDA_ERR_INVALID_PARAM;
    glenda_utcb_t *u = get_utcb(); utcb_clear(u); utcb_write(u, (const uint8_t *)data, size); u->mrs_regs[0] = size; u->msg_tag = msg_tag_new(PROTO_AUTH, AUTH_RPC, MSG_FLAG_HAS_BUFFER); glenda_error_t err = glenda_endpoint_call(client->endpoint); if (err == GLENDA_SUCCESS) { size_t n = u->size < out_size ? u->size : out_size; glenda_memcpy(out_data, u->ipc_buffer, n); *out_written = n; } return err;
}

glenda_error_t auth_client_proxy_call(glenda_auth_client_t *client, size_t target_cap, size_t label, size_t proto, const void *payload, size_t payload_size, void *out_data, size_t out_size, size_t *out_written)
{
    if (!client || !payload || !out_data || !out_written) return GLENDA_ERR_INVALID_PARAM;
    glenda_utcb_t *u = get_utcb(); utcb_clear(u); u->mrs_regs[0] = target_cap; u->mrs_regs[1] = label; u->mrs_regs[2] = proto; utcb_write(u, (const uint8_t *)payload, payload_size); u->msg_tag = msg_tag_new(PROTO_AUTH, AUTH_PROXY_CALL, MSG_FLAG_HAS_BUFFER); glenda_error_t err = glenda_endpoint_call(client->endpoint); if (err == GLENDA_SUCCESS) { size_t n = u->size < out_size ? u->size : out_size; glenda_memcpy(out_data, u->ipc_buffer, n); *out_written = n; } return err;
}
