#ifndef GLENDA_CAP_ENDPOINT_H
#define GLENDA_CAP_ENDPOINT_H

#include <glenda/cap.h>
#include <glenda/error.h>
#include <glenda/ipc.h>

glenda_error_t glenda_endpoint_send(glenda_cap_ptr_t endpoint, glenda_msg_tag_t msg_info, size_t *args);
glenda_error_t glenda_endpoint_recv(glenda_cap_ptr_t endpoint, glenda_cap_ptr_t reply_slot, size_t *out_val);
glenda_error_t glenda_endpoint_call(glenda_cap_ptr_t endpoint, glenda_msg_tag_t msg_info, size_t *args);
glenda_error_t glenda_endpoint_notify(glenda_cap_ptr_t endpoint, size_t badge);

#endif
