
#include <glenda/ipc.h>
#include <glenda/utils.h>

size_t utcb_available_space(glenda_utcb_t *utcb)
{
    return BUFFER_MAX_SIZE - utcb_available_data(utcb) - 1;
}

size_t utcb_available_data(glenda_utcb_t *utcb)
{
    size_t head = utcb->head;
    size_t tail = utcb->tail;

    if (tail >= head)
    {
        return tail - head;
    }
    else
    {
        return BUFFER_MAX_SIZE - head + tail;
    }
}

size_t utcb_write(glenda_utcb_t *utcb, const uint8_t *data, size_t len)
{
    size_t space = utcb_available_space(utcb);
    size_t to_write = len < space ? len : space;

    for (size_t i = 0; i < to_write; i++)
    {
        utcb->ipc_buffer[utcb->tail] = data[i];
        utcb->tail = (utcb->tail + 1) % BUFFER_MAX_SIZE;
    }
    return to_write;
}

size_t utcb_read(glenda_utcb_t *utcb, uint8_t *data, size_t len)
{
    size_t avail = utcb_available_data(utcb);
    size_t to_read = len < avail ? len : avail;

    for (size_t i = 0; i < to_read; i++)
    {
        data[i] = utcb->ipc_buffer[utcb->head];
        utcb->head = (utcb->head + 1) % BUFFER_MAX_SIZE;
    }
    return to_read;
}

void utcb_clear(glenda_utcb_t *utcb)
{
    utcb->head = 0;
    utcb->tail = 0;
}
