#include <glenda/client/time.h>
#include <glenda/cap/endpoint.h>
#include <glenda/ipc.h>

glenda_error_t time_client_init(glenda_time_client_t *client, glenda_cap_ptr_t endpoint){ if(!client) return GLENDA_ERR_INVALID_PARAM; client->endpoint=endpoint; return GLENDA_SUCCESS; }
glenda_error_t time_client_now(glenda_time_client_t *client, uint64_t *out_time){ if(!client||!out_time) return GLENDA_ERR_INVALID_PARAM; glenda_utcb_t *u=get_utcb(); utcb_clear(u); u->msg_tag=msg_tag_new(PROTO_TIME, TIME_NOW, MSG_FLAG_NONE); glenda_error_t e=glenda_endpoint_call(client->endpoint); if(e==GLENDA_SUCCESS) *out_time=u->mrs_regs[0]; return e; }
glenda_error_t time_client_mono_now(glenda_time_client_t *client, uint64_t *out_time){ if(!client||!out_time) return GLENDA_ERR_INVALID_PARAM; glenda_utcb_t *u=get_utcb(); utcb_clear(u); u->msg_tag=msg_tag_new(PROTO_TIME, TIME_MONO_NOW, MSG_FLAG_NONE); glenda_error_t e=glenda_endpoint_call(client->endpoint); if(e==GLENDA_SUCCESS) *out_time=u->mrs_regs[0]; return e; }
glenda_error_t time_client_sleep(glenda_time_client_t *client, size_t ms){ if(!client) return GLENDA_ERR_INVALID_PARAM; glenda_utcb_t *u=get_utcb(); utcb_clear(u); u->mrs_regs[0]=ms; u->msg_tag=msg_tag_new(PROTO_TIME, TIME_SLEEP, MSG_FLAG_NONE); return glenda_endpoint_call(client->endpoint); }
glenda_error_t time_client_adj_time(glenda_time_client_t *client, uint64_t absolute_ns, int64_t drift_ppb){ if(!client) return GLENDA_ERR_INVALID_PARAM; glenda_utcb_t *u=get_utcb(); utcb_clear(u); u->mrs_regs[0]=(size_t)absolute_ns; u->mrs_regs[1]=(size_t)drift_ppb; u->msg_tag=msg_tag_new(PROTO_TIME, TIME_ADJ_TIME, MSG_FLAG_NONE); return glenda_endpoint_call(client->endpoint); }
