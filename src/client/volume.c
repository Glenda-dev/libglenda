#include <glenda/client/volume.h>
#include <glenda/cap/endpoint.h>
#include <glenda/ipc.h>
#include <glenda/utils.h>

glenda_error_t volume_client_init(glenda_volume_client_t *client, glenda_cap_ptr_t endpoint){ if(!client) return GLENDA_ERR_INVALID_PARAM; client->endpoint=endpoint; return GLENDA_SUCCESS; }
glenda_error_t volume_client_get_device(glenda_volume_client_t *client, glenda_badge_t pid, glenda_cap_ptr_t recv, glenda_cap_ptr_t *out_endpoint){ (void)pid; (void)recv; (void)out_endpoint; if(!client) return GLENDA_ERR_INVALID_PARAM; return GLENDA_ERR_NOT_SUPPORTED; }
glenda_error_t volume_client_get_info(glenda_volume_client_t *client, glenda_volume_info_t *out_info){ if(!client||!out_info) return GLENDA_ERR_INVALID_PARAM; glenda_utcb_t *u=get_utcb(); utcb_clear(u); u->msg_tag=msg_tag_new(PROTO_VOLUME, VOLUME_GET_INFO, MSG_FLAG_NONE); glenda_error_t e=glenda_endpoint_call(client->endpoint); if(e==GLENDA_SUCCESS) *out_info = *(glenda_volume_info_t *)&u->ipc_buffer[0]; return e; }
