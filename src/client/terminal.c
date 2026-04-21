#include <glenda/client/terminal.h>
#include <glenda/cap/endpoint.h>
#include <glenda/ipc.h>
#include <glenda/utils.h>

glenda_error_t terminal_client_init(glenda_terminal_client_t *client, glenda_cap_ptr_t endpoint){ if(!client) return GLENDA_ERR_INVALID_PARAM; client->endpoint=endpoint; return GLENDA_SUCCESS; }
glenda_error_t terminal_client_set_mode(glenda_terminal_client_t *client, size_t mode){ if(!client) return GLENDA_ERR_INVALID_PARAM; glenda_utcb_t *u=get_utcb(); utcb_clear(u); u->mrs_regs[0]=mode; u->msg_tag=msg_tag_new(PROTO_TERMINAL, TERM_SET_MODE, MSG_FLAG_NONE); return glenda_endpoint_call(client->endpoint); }
glenda_error_t terminal_client_get_winsize(glenda_terminal_client_t *client, glenda_window_size_t *out_size){ if(!client||!out_size) return GLENDA_ERR_INVALID_PARAM; glenda_utcb_t *u=get_utcb(); utcb_clear(u); u->msg_tag=msg_tag_new(PROTO_TERMINAL, TERM_GET_WINSIZE, MSG_FLAG_NONE); glenda_error_t e=glenda_endpoint_call(client->endpoint); if(e==GLENDA_SUCCESS) *out_size = *(glenda_window_size_t *)&u->ipc_buffer[0]; return e; }
glenda_error_t terminal_client_set_winsize(glenda_terminal_client_t *client, glenda_window_size_t size){ if(!client) return GLENDA_ERR_INVALID_PARAM; glenda_utcb_t *u=get_utcb(); utcb_clear(u); glenda_memcpy(u->ipc_buffer, &size, sizeof(size)); u->size = sizeof(size); u->msg_tag=msg_tag_new(PROTO_TERMINAL, TERM_SET_WINSIZE, MSG_FLAG_HAS_BUFFER); return glenda_endpoint_call(client->endpoint); }
