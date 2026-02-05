#ifndef GLENDA_IPC_H
#define GLENDA_IPC_H

#include <glenda/glenda.h>
#include <glenda/cap.h>

typedef struct
{
    size_t raw;
} MsgTag;

typedef struct
{
    MsgTag msg_tag;
    size_t mrs_regs[MAX_MRS];
    CapPtr cap_transfer;
    CapPtr recv_window;
    Badge badge;
    size_t head;
    size_t tail;
    uint8_t ipc_buffer[BUFFER_MAX_SIZE];
} UTCB;

static inline UTCB *get_utcb(void)
{
    return (UTCB *)UTCB_VA;
}

static inline MsgTag msg_tag_new(size_t proto, size_t label, size_t flags)
{
    MsgTag tag;
    tag.raw = (proto & 0xFFFF) << 24 | (label & 0xFFFF) << 16 | (flags & 0xFFFF);
    return tag;
}

static inline size_t msg_tag_proto(MsgTag tag)
{
    return (tag.raw >> 24) & 0xFFFF;
}

static inline size_t msg_tag_label(MsgTag tag)
{
    return (tag.raw >> 16) & 0xFFFF;
}

static inline size_t msg_tag_flags(MsgTag tag)
{
    return tag.raw & 0xFFFF;
}

#endif
