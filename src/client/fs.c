#include <glenda/client/fs.h>
#include <glenda/cap/endpoint.h>
#include <glenda/ipc.h>
#include <glenda/utils.h>

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
    size_t path_len = glenda_strlen(path);
    utcb_write(utcb, (const uint8_t *)path, path_len);

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
