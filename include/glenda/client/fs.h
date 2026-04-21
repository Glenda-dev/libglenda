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
glenda_error_t fs_client_mkdir(glenda_fs_client_t *client, const char *path, uint32_t mode);
glenda_error_t fs_client_unlink(glenda_fs_client_t *client, const char *path);
glenda_error_t fs_client_rename(glenda_fs_client_t *client, const char *old_path, const char *new_path);
glenda_error_t fs_client_link(glenda_fs_client_t *client, const char *old_path, const char *new_path);
glenda_error_t fs_client_stat_path(glenda_fs_client_t *client, const char *path, glenda_stat_t *out_stat);
glenda_error_t fs_client_lstat_path(glenda_fs_client_t *client, const char *path, glenda_stat_t *out_stat);
glenda_error_t fs_client_readlink_path(glenda_fs_client_t *client, const char *path, char *buf, size_t buf_size, size_t *out_len);
glenda_error_t fs_client_read(glenda_fs_client_t *client, uint64_t offset, void *buf, size_t size, size_t *out_size);
glenda_error_t fs_client_write(glenda_fs_client_t *client, uint64_t offset, const void *buf, size_t size, size_t *out_size);
glenda_error_t fs_client_close(glenda_fs_client_t *client);
glenda_error_t fs_client_stat(glenda_fs_client_t *client, glenda_stat_t *out_stat);
glenda_error_t fs_client_getdents(glenda_fs_client_t *client, size_t count, glenda_dentry_t *buf, size_t buf_size, size_t *out_count);
glenda_error_t fs_client_seek(glenda_fs_client_t *client, int64_t offset, int whence, uint64_t *out_offset);
glenda_error_t fs_client_sync(glenda_fs_client_t *client);
glenda_error_t fs_client_truncate(glenda_fs_client_t *client, size_t size);
glenda_error_t fs_client_mount(glenda_fs_client_t *client, const char *path, glenda_cap_ptr_t target);
glenda_error_t fs_client_unmount(glenda_fs_client_t *client, const char *path);
glenda_error_t fs_client_create_view(glenda_fs_client_t *client, const char *root, size_t *out_view_id);
glenda_error_t fs_client_set_view(glenda_fs_client_t *client, size_t view_id);

#endif /* GLENDA_CLIENT_FS_H */
