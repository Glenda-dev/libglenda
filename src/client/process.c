#include <glenda/client/process.h>
#include <glenda/cap/endpoint.h>
#include <glenda/ipc.h>
#include <glenda/protocol.h>

glenda_error_t process_client_init(glenda_process_client_t *client, glenda_cap_ptr_t endpoint)
{
    if (!client)
    {
        return GLENDA_ERR_INVALID_PARAM;
    }
    client->endpoint = endpoint;
    return GLENDA_SUCCESS;
}

glenda_error_t process_client_exit(glenda_process_client_t *client, int code)
{
    if (!client)
    {
        return GLENDA_ERR_INVALID_PARAM;
    }

    size_t args[MAX_MRS] = {(size_t)code, 0, 0, 0, 0, 0, 0, 0};
    glenda_msg_tag_t tag = msg_tag_new(PROTO_PROCESS, PROC_EXIT, 0);

    return glenda_endpoint_call(client->endpoint, tag, args);
}
