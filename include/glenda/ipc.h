#ifndef GLENDA_IPC_H
#define GLENDA_IPC_H

#include <glenda/types.h>
#include <glenda/arch.h>
#include <glenda/mem.h>

#define MAX_MRS 8
#define IPC_BUFFER_SIZE (3 * 1024)

#define MSG_FLAG_NONE 0x0
#define MSG_FLAG_HAS_CAP 0x1
#define MSG_FLAG_HAS_BUFFER 0x2
#define MSG_FLAG_NON_BLOCKING 0x4

typedef struct
{
    glenda_msg_tag_t msg_tag;
    size_t mrs_regs[MAX_MRS];
    glenda_cap_ptr_t cap_transfer;
    glenda_cap_ptr_t recv_window;
    glenda_cap_ptr_t reply_window;
    glenda_badge_t badge;
    size_t head;
    size_t size;
    uint8_t ipc_buffer[IPC_BUFFER_SIZE];
} glenda_utcb_t;

static inline glenda_utcb_t *get_utcb(void)
{
    return (glenda_utcb_t *)UTCB_VA;
}

static inline glenda_msg_tag_t msg_tag_new(size_t proto, size_t label, size_t flags)
{
    glenda_msg_tag_t tag;
    tag.raw = (proto & 0xFFFF) << 24 | (label & 0xFFFF) << 16 | (flags & 0xFFFF);
    return tag;
}

static inline size_t msg_tag_proto(glenda_msg_tag_t tag)
{
    return (tag.raw >> 24) & 0xFFFF;
}

static inline size_t msg_tag_label(glenda_msg_tag_t tag)
{
    return (tag.raw >> 16) & 0xFFFF;
}

static inline size_t msg_tag_flags(glenda_msg_tag_t tag)
{
    return tag.raw & 0xFFFF;
}

size_t utcb_available_space(glenda_utcb_t *utcb);
size_t utcb_available_data(glenda_utcb_t *utcb);
size_t utcb_write(glenda_utcb_t *utcb, const uint8_t *data, size_t len);
size_t utcb_append(glenda_utcb_t *utcb, const uint8_t *data, size_t len);
size_t utcb_read(glenda_utcb_t *utcb, uint8_t *data, size_t len);
void utcb_clear(glenda_utcb_t *utcb);

#endif
