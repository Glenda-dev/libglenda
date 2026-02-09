
#include <glenda/ipc.h>
#include <glenda/utils.h>

size_t utcb_available_space(glenda_utcb_t *utcb)
{
    return IPC_BUFFER_SIZE - utcb->size;
}

size_t utcb_available_data(glenda_utcb_t *utcb)
{
    return utcb->size - utcb->head;
}

size_t utcb_write(glenda_utcb_t *utcb, const uint8_t *data, size_t len)
{
    size_t to_write = len < IPC_BUFFER_SIZE ? len : IPC_BUFFER_SIZE;

    for (size_t i = 0; i < to_write; i++)
    {
        utcb->ipc_buffer[i] = data[i];
    }
    utcb->size = to_write;
    utcb->head = 0;
    return to_write;
}

size_t utcb_append(glenda_utcb_t *utcb, const uint8_t *data, size_t len)
{
    size_t space = utcb_available_space(utcb);
    size_t to_write = len < space ? len : space;

    for (size_t i = 0; i < to_write; i++)
    {
        utcb->ipc_buffer[utcb->size + i] = data[i];
    }
    utcb->size += to_write;
    return to_write;
}

size_t utcb_read(glenda_utcb_t *utcb, uint8_t *data, size_t len)
{
    size_t avail = utcb_available_data(utcb);
    size_t to_read = len < avail ? len : avail;

    for (size_t i = 0; i < to_read; i++)
    {
        data[i] = utcb->ipc_buffer[utcb->head + i];
    }
    utcb->head += to_read;
    return to_read;
}

void utcb_clear(glenda_utcb_t *utcb)
{
    utcb->size = 0;
    utcb->head = 0;
}
