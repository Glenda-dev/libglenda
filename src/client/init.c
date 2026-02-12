#include <glenda/client/init.h>
#include <glenda/cap/endpoint.h>
#include <glenda/ipc.h>
#include <glenda/utils.h>

glenda_error_t init_client_init(glenda_init_client_t *client, glenda_cap_ptr_t endpoint)
{
    if (!client)
        return GLENDA_ERR_INVALID_PARAM;
    client->endpoint = endpoint;
    return GLENDA_SUCCESS;
}

static glenda_error_t init_client_service_op(glenda_init_client_t *client, const char *service, size_t label)
{
    glenda_utcb_t *utcb = get_utcb();
    utcb_clear(utcb);
    size_t len = glenda_strlen(service);
    utcb_write(utcb, (const uint8_t *)service, len);
    utcb->msg_tag = msg_tag_new(PROTO_INIT, label, MSG_FLAG_NONE);
    return glenda_endpoint_call(client->endpoint);
}

glenda_error_t init_client_start_service(glenda_init_client_t *client, const char *service)
{
    return init_client_service_op(client, service, INIT_SERVICE_START);
}

glenda_error_t init_client_stop_service(glenda_init_client_t *client, const char *service)
{
    return init_client_service_op(client, service, INIT_SERVICE_STOP);
}

glenda_error_t init_client_restart_service(glenda_init_client_t *client, const char *service)
{
    return init_client_service_op(client, service, INIT_SERVICE_RESTART);
}

glenda_error_t init_client_reload_service(glenda_init_client_t *client, const char *service)
{
    return init_client_service_op(client, service, INIT_SERVICE_RELOAD);
}
