#ifndef GLENDA_TYPES_H
#define GLENDA_TYPES_H

#include <glenda/stddef.h>
#include <glenda/stdint.h>

typedef size_t glenda_cap_ptr_t;
typedef size_t glenda_badge_t;

typedef struct
{
    size_t raw;
} glenda_msg_tag_t;

#endif /* GLENDA_TYPES_H */
