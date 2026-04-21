#ifndef GLENDA_CLIENT_TERMINAL_H
#define GLENDA_CLIENT_TERMINAL_H

#include <glenda/types.h>
#include <glenda/error.h>
#include <glenda/protocol.h>

typedef struct
{
    glenda_cap_ptr_t endpoint;
} glenda_terminal_client_t;

glenda_error_t terminal_client_init(glenda_terminal_client_t *client, glenda_cap_ptr_t endpoint);
glenda_error_t terminal_client_set_mode(glenda_terminal_client_t *client, size_t mode);
glenda_error_t terminal_client_get_winsize(glenda_terminal_client_t *client, glenda_window_size_t *out_size);
glenda_error_t terminal_client_set_winsize(glenda_terminal_client_t *client, glenda_window_size_t size);

#endif
