#ifndef GLENDA_CLIENT_FS_H
#define GLENDA_CLIENT_FS_H

#include <glenda/types.h>
#include <glenda/error.h>
#include <glenda/protocol.h>

typedef struct
{
    glenda_cap_ptr_t endpoint;
} glenda_fs_client_t;

glenda_error_t fs_client_init(glenda_fs_client_t *client, glenda_cap_ptr_t endpoint);
glenda_error_t fs_client_open(glenda_fs_client_t *client, const char *path, uint32_t flags, uint32_t mode, glenda_cap_ptr_t *out_cap);
glenda_error_t fs_client_read(glenda_fs_client_t *client, uint64_t offset, void *buf, size_t size, size_t *out_size);
glenda_error_t fs_client_write(glenda_fs_client_t *client, uint64_t offset, const void *buf, size_t size, size_t *out_size);
glenda_error_t fs_client_close(glenda_fs_client_t *client);
glenda_error_t fs_client_seek(glenda_fs_client_t *client, int64_t offset, int whence, uint64_t *out_offset);

#endif /* GLENDA_CLIENT_FS_H */
