#include <glenda/client/fs.h>
#include <glenda/cap/endpoint.h>
#include <glenda/ipc.h>
#include <glenda/utils.h>

static glenda_error_t fs_client_send_str(glenda_fs_client_t *client, size_t label, const char *path)
{
    glenda_utcb_t *utcb = get_utcb();
    utcb_clear(utcb);
    utcb_write(utcb, (const uint8_t *)path, glenda_strlen(path));
    utcb->msg_tag = msg_tag_new(PROTO_FS, label, MSG_FLAG_HAS_BUFFER);
    return glenda_endpoint_call(client->endpoint);
}

glenda_error_t fs_client_init(glenda_fs_client_t *client, glenda_cap_ptr_t endpoint)
{
    if (!client)
    {
        return GLENDA_ERR_INVALID_PARAM;
    }
    client->endpoint = endpoint;
    return GLENDA_SUCCESS;
}

glenda_error_t fs_client_open(glenda_fs_client_t *client, const char *path, uint32_t flags, uint32_t mode, glenda_cap_ptr_t *out_cap)
{
    if (!client || !path || !out_cap)
    {
        return GLENDA_ERR_INVALID_PARAM;
    }

    glenda_utcb_t *utcb = get_utcb();
    utcb_clear(utcb);
    utcb_write(utcb, (const uint8_t *)path, glenda_strlen(path));
    utcb->mrs_regs[0] = (size_t)flags;
    utcb->mrs_regs[1] = (size_t)mode;
    for (int i = 2; i < MAX_MRS; i++)
        utcb->mrs_regs[i] = 0;
    glenda_msg_tag_t tag = msg_tag_new(PROTO_FS, FS_OPEN, 0);
    utcb->msg_tag = tag;

    glenda_error_t err = glenda_endpoint_call(client->endpoint);
    if (err == GLENDA_SUCCESS)
    {
        *out_cap = (glenda_cap_ptr_t)utcb->mrs_regs[0];
    }
    return err;
}

glenda_error_t fs_client_mkdir(glenda_fs_client_t *client, const char *path, uint32_t mode)
{
    if (!client || !path)
        return GLENDA_ERR_INVALID_PARAM;
    glenda_utcb_t *utcb = get_utcb();
    utcb_clear(utcb);
    utcb_write(utcb, (const uint8_t *)path, glenda_strlen(path));
    utcb->mrs_regs[0] = (size_t)mode;
    utcb->msg_tag = msg_tag_new(PROTO_FS, FS_MKDIR, MSG_FLAG_HAS_BUFFER);
    return glenda_endpoint_call(client->endpoint);
}

glenda_error_t fs_client_unlink(glenda_fs_client_t *client, const char *path)
{
    if (!client || !path)
        return GLENDA_ERR_INVALID_PARAM;
    return fs_client_send_str(client, FS_UNLINK, path);
}

glenda_error_t fs_client_rename(glenda_fs_client_t *client, const char *old_path, const char *new_path)
{
    if (!client || !old_path || !new_path)
        return GLENDA_ERR_INVALID_PARAM;
    glenda_utcb_t *utcb = get_utcb();
    utcb_clear(utcb);
    utcb_write(utcb, (const uint8_t *)old_path, glenda_strlen(old_path));
    utcb_append(utcb, (const uint8_t *)"", 1);
    utcb_append(utcb, (const uint8_t *)new_path, glenda_strlen(new_path));
    utcb->msg_tag = msg_tag_new(PROTO_FS, FS_RENAME, MSG_FLAG_HAS_BUFFER);
    return glenda_endpoint_call(client->endpoint);
}

glenda_error_t fs_client_link(glenda_fs_client_t *client, const char *old_path, const char *new_path)
{
    if (!client || !old_path || !new_path)
        return GLENDA_ERR_INVALID_PARAM;
    glenda_utcb_t *utcb = get_utcb();
    utcb_clear(utcb);
    utcb_write(utcb, (const uint8_t *)old_path, glenda_strlen(old_path));
    utcb_append(utcb, (const uint8_t *)"", 1);
    utcb_append(utcb, (const uint8_t *)new_path, glenda_strlen(new_path));
    utcb->msg_tag = msg_tag_new(PROTO_FS, FS_LINK, MSG_FLAG_HAS_BUFFER);
    return glenda_endpoint_call(client->endpoint);
}

glenda_error_t fs_client_stat_path(glenda_fs_client_t *client, const char *path, glenda_stat_t *out_stat)
{
    if (!client || !path || !out_stat)
        return GLENDA_ERR_INVALID_PARAM;
    glenda_error_t err = fs_client_send_str(client, FS_STAT_PATH, path);
    if (err == GLENDA_SUCCESS)
        *out_stat = *(glenda_stat_t *)&get_utcb()->ipc_buffer[0];
    return err;
}

glenda_error_t fs_client_lstat_path(glenda_fs_client_t *client, const char *path, glenda_stat_t *out_stat)
{
    if (!client || !path || !out_stat)
        return GLENDA_ERR_INVALID_PARAM;
    glenda_error_t err = fs_client_send_str(client, FS_LSTAT_PATH, path);
    if (err == GLENDA_SUCCESS)
        *out_stat = *(glenda_stat_t *)&get_utcb()->ipc_buffer[0];
    return err;
}

glenda_error_t fs_client_readlink_path(glenda_fs_client_t *client, const char *path, char *buf, size_t buf_size, size_t *out_len)
{
    if (!client || !path || !buf || !out_len)
        return GLENDA_ERR_INVALID_PARAM;
    glenda_error_t err = fs_client_send_str(client, FS_READLINK_PATH, path);
    if (err == GLENDA_SUCCESS)
    {
        size_t len = get_utcb()->size;
        if (len > buf_size)
            len = buf_size;
        glenda_memcpy(buf, get_utcb()->ipc_buffer, len);
        *out_len = len;
    }
    return err;
}

glenda_error_t fs_client_read(glenda_fs_client_t *client, uint64_t offset, void *buf, size_t size, size_t *out_size)
{
    if (!client || !buf || !out_size)
    {
        return GLENDA_ERR_INVALID_PARAM;
    }

    glenda_utcb_t *utcb = get_utcb();
    utcb_clear(utcb);

    utcb->mrs_regs[0] = size;
    utcb->mrs_regs[1] = (size_t)offset;
    for (int i = 2; i < MAX_MRS; i++)
        utcb->mrs_regs[i] = 0;
    glenda_msg_tag_t tag = msg_tag_new(PROTO_FS, FS_READ, 0);
    utcb->msg_tag = tag;

    glenda_error_t err = glenda_endpoint_call(client->endpoint);
    if (err == GLENDA_SUCCESS)
    {
        size_t read_len = utcb->size;
        if (read_len > size)
        {
            read_len = size;
        }
        glenda_memcpy(buf, utcb->ipc_buffer, read_len);
        *out_size = read_len;
    }
    return err;
}

glenda_error_t fs_client_write(glenda_fs_client_t *client, uint64_t offset, const void *buf, size_t size, size_t *out_size)
{
    if (!client || !buf || !out_size)
    {
        return GLENDA_ERR_INVALID_PARAM;
    }

    glenda_utcb_t *utcb = get_utcb();
    utcb_clear(utcb);

    // Respect UTCB buffer limits
    size_t to_write = size > IPC_BUFFER_SIZE ? IPC_BUFFER_SIZE : size;
    utcb_write(utcb, (const uint8_t *)buf, to_write);

    utcb->mrs_regs[0] = to_write;
    utcb->mrs_regs[1] = (size_t)offset;
    for (int i = 2; i < MAX_MRS; i++)
        utcb->mrs_regs[i] = 0;
    glenda_msg_tag_t tag = msg_tag_new(PROTO_FS, FS_WRITE, 0);
    utcb->msg_tag = tag;

    glenda_error_t err = glenda_endpoint_call(client->endpoint);
    if (err == GLENDA_SUCCESS)
    {
        *out_size = utcb->mrs_regs[0];
    }
    return err;
}

glenda_error_t fs_client_close(glenda_fs_client_t *client)
{
    if (!client)
    {
        return GLENDA_ERR_INVALID_PARAM;
    }

    glenda_utcb_t *utcb = get_utcb();
    for (int i = 0; i < MAX_MRS; i++)
        utcb->mrs_regs[i] = 0;
    glenda_msg_tag_t tag = msg_tag_new(PROTO_FS, FS_CLOSE, 0);
    utcb->msg_tag = tag;

    return glenda_endpoint_call(client->endpoint);
}

glenda_error_t fs_client_stat(glenda_fs_client_t *client, glenda_stat_t *out_stat)
{
    if (!client || !out_stat)
        return GLENDA_ERR_INVALID_PARAM;
    glenda_utcb_t *utcb = get_utcb();
    utcb_clear(utcb);
    utcb->msg_tag = msg_tag_new(PROTO_FS, FS_STAT, 0);
    glenda_error_t err = glenda_endpoint_call(client->endpoint);
    if (err == GLENDA_SUCCESS)
        *out_stat = *(glenda_stat_t *)&utcb->ipc_buffer[0];
    return err;
}

glenda_error_t fs_client_getdents(glenda_fs_client_t *client, size_t count, glenda_dentry_t *buf, size_t buf_size, size_t *out_count)
{
    if (!client || !buf || !out_count)
        return GLENDA_ERR_INVALID_PARAM;
    glenda_utcb_t *utcb = get_utcb();
    utcb_clear(utcb);
    utcb->mrs_regs[1] = count;
    utcb->msg_tag = msg_tag_new(PROTO_FS, FS_GETDENTS, 0);
    glenda_error_t err = glenda_endpoint_call(client->endpoint);
    if (err == GLENDA_SUCCESS)
    {
        size_t bytes = utcb->size;
        if (bytes > buf_size * sizeof(glenda_dentry_t))
            bytes = buf_size * sizeof(glenda_dentry_t);
        glenda_memcpy(buf, utcb->ipc_buffer, bytes);
        *out_count = bytes / sizeof(glenda_dentry_t);
    }
    return err;
}

glenda_error_t fs_client_seek(glenda_fs_client_t *client, int64_t offset, int whence, uint64_t *out_offset)
{
    if (!client || !out_offset)
    {
        return GLENDA_ERR_INVALID_PARAM;
    }

    glenda_utcb_t *utcb = get_utcb();
    utcb->mrs_regs[0] = (size_t)offset;
    utcb->mrs_regs[1] = (size_t)whence;
    for (int i = 2; i < MAX_MRS; i++)
        utcb->mrs_regs[i] = 0;
    glenda_msg_tag_t tag = msg_tag_new(PROTO_FS, FS_SEEK, 0);
    utcb->msg_tag = tag;

    glenda_error_t err = glenda_endpoint_call(client->endpoint);
    if (err == GLENDA_SUCCESS)
    {
        *out_offset = (uint64_t)utcb->mrs_regs[0];
    }
    return err;
}

glenda_error_t fs_client_sync(glenda_fs_client_t *client)
{
    if (!client)
        return GLENDA_ERR_INVALID_PARAM;
    glenda_utcb_t *utcb = get_utcb();
    utcb_clear(utcb);
    utcb->msg_tag = msg_tag_new(PROTO_FS, FS_SYNC, 0);
    return glenda_endpoint_call(client->endpoint);
}

glenda_error_t fs_client_truncate(glenda_fs_client_t *client, size_t size)
{
    if (!client)
        return GLENDA_ERR_INVALID_PARAM;
    glenda_utcb_t *utcb = get_utcb();
    utcb_clear(utcb);
    utcb->mrs_regs[0] = size;
    utcb->msg_tag = msg_tag_new(PROTO_FS, FS_TRUNCATE, 0);
    return glenda_endpoint_call(client->endpoint);
}

glenda_error_t fs_client_mount(glenda_fs_client_t *client, const char *path, glenda_cap_ptr_t target)
{
    if (!client || !path)
        return GLENDA_ERR_INVALID_PARAM;
    glenda_utcb_t *utcb = get_utcb();
    utcb_clear(utcb);
    utcb_write(utcb, (const uint8_t *)path, glenda_strlen(path));
    utcb->cap_transfer = target;
    utcb->msg_tag = msg_tag_new(PROTO_FS, FS_MOUNT, MSG_FLAG_HAS_BUFFER | MSG_FLAG_HAS_CAP);
    return glenda_endpoint_call(client->endpoint);
}

glenda_error_t fs_client_unmount(glenda_fs_client_t *client, const char *path)
{
    if (!client || !path)
        return GLENDA_ERR_INVALID_PARAM;
    return fs_client_send_str(client, FS_UNMOUNT, path);
}

glenda_error_t fs_client_create_view(glenda_fs_client_t *client, const char *root, size_t *out_view_id)
{
    if (!client || !root || !out_view_id)
        return GLENDA_ERR_INVALID_PARAM;
    glenda_error_t err = fs_client_send_str(client, FS_CREATE_VIEW, root);
    if (err == GLENDA_SUCCESS)
        *out_view_id = get_utcb()->mrs_regs[0];
    return err;
}

glenda_error_t fs_client_set_view(glenda_fs_client_t *client, size_t view_id)
{
    if (!client)
        return GLENDA_ERR_INVALID_PARAM;
    glenda_utcb_t *utcb = get_utcb();
    utcb_clear(utcb);
    utcb->mrs_regs[0] = view_id;
    utcb->msg_tag = msg_tag_new(PROTO_FS, FS_SET_VIEW, 0);
    return glenda_endpoint_call(client->endpoint);
}
