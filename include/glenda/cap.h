#ifndef GLENDA_CAP_H
#define GLENDA_CAP_H

#include <glenda/types.h>

static const glenda_cap_ptr_t CAP_CSPACE = 1;
static const glenda_cap_ptr_t CAP_VSPACE = 2;
static const glenda_cap_ptr_t CAP_TCB = 3;
static const glenda_cap_ptr_t CAP_MON = 4;
static const glenda_cap_ptr_t CAP_KERNEL = 5;
static const glenda_cap_ptr_t CAP_REPLY = 10;
static const glenda_cap_ptr_t CAP_APE = 11;

typedef enum
{
    CAP_TYPE_EMPTY = 0,
    CAP_TYPE_UNTYPED = 1,
    CAP_TYPE_TCB = 2,
    CAP_TYPE_ENDPOINT = 3,
    CAP_TYPE_REPLY = 4,
    CAP_TYPE_FRAME = 5,
    CAP_TYPE_PAGETABLE = 6,
    CAP_TYPE_CNODE = 7,
    CAP_TYPE_IRQ_HANDLER = 8,
    CAP_TYPE_KERNEL = 9,
    CAP_TYPE_VSPACE = 10,
} glenda_cap_type_t;

typedef enum
{
    CAP_RIGHTS_NONE = 0,
    CAP_RIGHTS_READ = 1 << 0,
    CAP_RIGHTS_WRITE = 1 << 1,
    CAP_RIGHTS_GRANT = 1 << 2,
    CAP_RIGHTS_SEND = 1 << 3,
    CAP_RIGHTS_RECV = 1 << 4,
    CAP_RIGHTS_CALL = 1 << 5,
    CAP_RIGHTS_EXECUTE = 1 << 6,
    CAP_RIGHTS_ALL = 0xFF,
} glenda_cap_rights_t;

#endif
