#ifndef GLENDA_CLIENT_TIME_H
#define GLENDA_CLIENT_TIME_H

#include <glenda/types.h>
#include <glenda/error.h>
#include <glenda/protocol.h>

typedef struct
{
    glenda_cap_ptr_t endpoint;
} glenda_time_client_t;

glenda_error_t time_client_init(glenda_time_client_t *client, glenda_cap_ptr_t endpoint);
glenda_error_t time_client_now(glenda_time_client_t *client, uint64_t *out_time);
glenda_error_t time_client_mono_now(glenda_time_client_t *client, uint64_t *out_time);
glenda_error_t time_client_sleep(glenda_time_client_t *client, size_t ms);
glenda_error_t time_client_adj_time(glenda_time_client_t *client, uint64_t absolute_ns, int64_t drift_ppb);

#endif
