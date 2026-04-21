#ifndef GLENDA_PROTOCOL_H
#define GLENDA_PROTOCOL_H

// Core Protocols
#define PROTO_GENERIC 0x0000
#define PROTO_KERNEL 0x0100
#define PROTO_PROCESS 0x0200
#define PROTO_RESOURCE 0x0300
#define PROTO_DEVICE 0x0400
#define PROTO_INIT 0x0500
#define PROTO_FS 0x0600
#define PROTO_NETWORK 0x0700
#define PROTO_AUTH 0x0800
#define PROTO_VOLUME 0x0900
#define PROTO_TIME 0x0A00
#define PROTO_TERMINAL 0x0B00
#define PROTO_INPUT 0x0C00
#define PROTO_LINUX 0x0D00

// ==========================================
// FS Protocol (0x600)
// ==========================================

// Namespace Operations
#define FS_OPEN 0x01
#define FS_MKDIR 0x02
#define FS_UNLINK 0x03
#define FS_STAT_PATH 0x04
#define FS_RENAME 0x05
#define FS_LSTAT_PATH 0x06
#define FS_READLINK_PATH 0x07
#define FS_LINK 0x08

// File Handle Operations
#define FS_CLOSE 0x10
#define FS_STAT 0x11
#define FS_SETATTR 0x12
#define FS_READ 0x13
#define FS_WRITE 0x14
#define FS_GETDENTS 0x15
#define FS_SYNC 0x16
#define FS_SEEK 0x17
#define FS_TRUNCATE 0x18
#define FS_IOCTL 0x19
#define FS_SETUP_IOURING 0x20
#define FS_PROCESS_IOURING 0x21
#define FS_MAP_PAGE 0x22
#define FS_UNMAP_PAGE 0x23
#define FS_IOCTL_EX 0x24

// Pipe Operations
#define FS_PIPE 0x30

// Virtual Filesystem Operations
#define FS_MOUNT 0x40
#define FS_UNMOUNT 0x41
#define FS_CREATE_VIEW 0x42
#define FS_SET_VIEW 0x43

typedef struct
{
    uint64_t dev;
    uint64_t ino;
    uint32_t mode;
    uint32_t nlink;
    uint32_t uid;
    uint32_t gid;
    uint64_t size;
    int64_t atime_sec;
    int64_t atime_nsec;
    int64_t mtime_sec;
    int64_t mtime_nsec;
    int64_t ctime_sec;
    int64_t ctime_nsec;
    int64_t blksize;
    int64_t blocks;
} glenda_stat_t;

typedef struct
{
    uint64_t ino;
    uint64_t off;
    uint16_t reclen;
    uint8_t type;
    char name[256];
} glenda_dentry_t;

// Open Flags (Octal for traditional compat, but defined as hex/dec here)
#define O_RDONLY 00
#define O_WRONLY 01
#define O_RDWR 02
#define O_CREAT 0100
#define O_EXCL 0200
#define O_TRUNC 01000
#define O_APPEND 02000
#define O_DIRECTORY 0200000

// ==========================================
// Process Protocol (0x200)
// ==========================================
#define PROC_SPAWN 0x01
#define PROC_EXEC 0x02
#define PROC_EXIT 0x03
#define PROC_WAIT 0x04
#define PROC_KILL 0x05
#define PROC_FORK 0x06

#define PROC_THREAD_CREATE 0x10
#define PROC_THREAD_EXIT 0x11
#define PROC_THREAD_JOIN 0x12
#define PROC_FUTEX_WAIT 0x13
#define PROC_FUTEX_WAKE 0x14
#define PROC_YIELD 0x15
#define PROC_SLEEP 0x16

#define PROC_GET_PID 0x20
#define PROC_GET_PPID 0x21

#define PROC_GET_CNODE 0x30

// ==========================================
// Device Protocol (0x400)
// ==========================================
#define DEVICE_GET_DESC 0x01
#define DEVICE_GET_MMIO 0x02
#define DEVICE_GET_IRQ 0x03
#define DEVICE_SCAN_PLATFORM 0x04

// UART Methods (Specific labels for UART devices)
#define UART_PUT_CHAR 0x01
#define UART_GET_CHAR 0x02
#define UART_PUT_STR 0x03
#define UART_SET_BAUD 0x04

// ==========================================
// Init Protocol (0x500)
// ==========================================
#define INIT_SERVICE_START 0x01
#define INIT_SERVICE_STOP 0x02
#define INIT_SERVICE_RESTART 0x03
#define INIT_SERVICE_RELOAD 0x04
#define INIT_SERVICE_QUERY 0x05
#define INIT_SERVICE_LIST 0x06

// Init Capabilities
#define INIT_CAP_CONSOLE 1
#define INIT_CAP_INITRD 2
#define INIT_CAP_UNTYPED 3
#define INIT_CAP_MMIO 4
#define INIT_CAP_IRQ 5

// Init Resources
#define INIT_RESOURCE_BOOT_ARGS 1
#define INIT_RESOURCE_PLATFORM_INFO 2
#define INIT_RESOURCE_INITRD_INFO 3
#define INIT_RESOURCE_UNTYPED_INFO 4
#define INIT_RESOURCE_MMIO_INFO 5
#define INIT_RESOURCE_IRQ_INFO 6

// ==========================================
// Kernel / Fault Protocol (0x100)
// ==========================================
// These are often delivered as IPC messages to fault handlers
#define FAULT_SYSCALL 0x01
#define FAULT_PAGE_FAULT 0x02
#define FAULT_ILLEGAL_INSTRUCTION 0x03
#define FAULT_BREAKPOINT 0x04
#define FAULT_ACCESS_FAULT 0x05
#define FAULT_ACCESS_MISALIGNED 0x06
#define FAULT_UNKNOWN_FAULT 0x07
#define FAULT_IRQ 0x08

// ==========================================
// Network Protocol (0x700)
// ==========================================

#define NETWORK_SOCKET 0x01
#define NETWORK_BIND 0x10
#define NETWORK_LISTEN 0x11
#define NETWORK_ACCEPT 0x12
#define NETWORK_CONNECT 0x13
#define NETWORK_SEND 0x14
#define NETWORK_RECV 0x15
#define NETWORK_CLOSE 0x16
#define NETWORK_GETSOCKNAME 0x17
#define NETWORK_GETPEERNAME 0x18
#define NETWORK_SETSOCKOPT 0x19
#define NETWORK_GETSOCKOPT 0x1A
// Address Familes (Domain)
#define AF_INET 2
#define AF_INET6 10

// Socket Types
#define SOCK_STREAM 1
#define SOCK_DGRAM 2
#define SOCK_RAW 3

// Protocol Constants
#define IPPROTO_IP 0
#define IPPROTO_ICMP 1
#define IPPROTO_TCP 6
#define IPPROTO_UDP 17
#define IPPROTO_IPV6 41
#define IPPROTO_RAW 255

// ==========================================
// Auth Protocol (0x800)
// ==========================================
#define AUTH_NEGOTIATE 0x00
#define AUTH_RPC 0x01
#define AUTH_GET_TICKET 0x02
#define AUTH_LOGOUT 0x03
#define AUTH_PROXY_CALL 0x04
#define AUTH_VALIDATE_TICKET 0x05
#define AUTH_GET_IDENTITY 0x10
#define AUTH_SET_IDENTITY 0x11
#define AUTH_CHECK_PERMISSION 0x20
#define AUTH_UPSERT_POLICY 0x21
#define AUTH_DELETE_POLICY 0x22
#define AUTH_SET_POLICY_BACKEND 0x23
#define AUTH_CLEAR_POLICY_BACKEND 0x24
#define AUTH_GET_POLICY_BACKEND_STATUS 0x25

typedef struct
{
    uint32_t uid;
    uint32_t gid;
    uint32_t euid;
    uint32_t egid;
} glenda_identity_info_t;

typedef struct
{
    uint8_t allowed;
    uint8_t reserved[3];
    uint32_t ttl_ms;
} glenda_permission_decision_t;

typedef struct
{
    uint32_t subject;
    uint8_t effect;
    uint8_t reserved[3];
    uint32_t ttl_ms;
} glenda_policy_rule_t;

typedef struct
{
    uint8_t external_attached;
    uint8_t reserved[3];
    uint32_t generation;
} glenda_policy_backend_status_t;

// ==========================================
// Time Protocol (0x900)
// ==========================================
#define TIME_NOW 0x01
#define TIME_SLEEP 0x02
#define TIME_ADJ_TIME 0x03
#define TIME_MONO_NOW 0x04

// ==========================================
// Volume Protocol (0xA00)
// ==========================================
#define VOLUME_GET_DEVICE 0x01
#define VOLUME_GET_INFO 0x02

typedef struct
{
    size_t size;
    uint32_t block_size;
    uint8_t fs_type[16];
} glenda_volume_info_t;

// ==========================================
// Terminal Protocol (0xB00)
// ==========================================
#define TERM_PUT_STR 0x01
#define TERM_GET_STR 0x02
#define TERM_GET_CHAR 0x03
#define TERM_PUT_CHAR 0x04
#define TERM_POLL_READ 0x05
#define TERM_GET_URING 0x11
#define TERM_SET_MODE 0x12
#define TERM_GET_WINSIZE 0x13
#define TERM_SET_WINSIZE 0x14
#define TERM_SET_DISPLAY 0x15
#define TERM_GET_TERMIOS 0x16
#define TERM_SET_TERMIOS 0x17
#define TERM_GET_PGRP 0x18
#define TERM_SET_PGRP 0x19
#define TERM_STREAM_READ 0x40
#define TERM_STREAM_WRITE 0x41
#define TERM_STREAM_POLL 0x42
#define TERM_STREAM_SET_MODE 0x43
#define TERM_NATIVE_GET_EVENT 0x50
#define TERM_NATIVE_POLL_EVENT 0x51
#define TERM_NATIVE_PUT_TEXT 0x52
#define VTS_ALLOC_VT 0x21
#define VTS_FREE_VT 0x22
#define VTS_LIST_VTS 0x23
#define VTS_LIST_SEATS 0x24
#define VTS_SWITCH_VT 0x25
#define VTS_BIND_SEAT 0x26
#define VTS_SET_EXCLUSIVE 0x27
#define VTS_OPEN_VT 0x28
#define VTS_GET_PTY_LOCK 0x29
#define VTS_SET_PTY_LOCK 0x2A
#define SEAT_BIND_DEVICE 0x30
#define SEAT_UNBIND_DEVICE 0x31

typedef struct
{
    uint16_t rows;
    uint16_t cols;
    uint16_t xpixel;
    uint16_t ypixel;
} glenda_window_size_t;

// ==========================================
// Input Protocol (0xC00)
// ==========================================
#define INPUT_GET_DEVICE 0x01
#define INPUT_GET_INFO 0x02
#define INPUT_SET_MODE 0x10
#define INPUT_SET_GRAB 0x11
#define INPUT_POLL_EVENT 0x12

// ==========================================
// Resource Protocol (0x300)
// ==========================================
#define RESOURCE_ALLOC 0x01
#define RESOURCE_FREE 0x02
#define RESOURCE_DMA_ALLOC 0x03
#define RESOURCE_MAP 0x10
#define RESOURCE_UNMAP 0x11
#define RESOURCE_CLONE 0x12
#define RESOURCE_MMAP 0x20
#define RESOURCE_MUNMAP 0x21
#define RESOURCE_SBRK 0x22
#define RESOURCE_GETCAP 0x30
#define RESOURCE_REGISTER_CAP 0x31
#define RESOURCE_GET_CONFIG 0x32

typedef enum
{
    RESOURCE_TYPE_UNKNOWN = 0,
    RESOURCE_TYPE_KERNEL = 1,
    RESOURCE_TYPE_UNTYPED = 2,
    RESOURCE_TYPE_BOOTINFO = 3,
    RESOURCE_TYPE_MMIO = 4,
    RESOURCE_TYPE_IRQ = 5,
    RESOURCE_TYPE_PLATFORM = 6,
    RESOURCE_TYPE_ENDPOINT = 7,
} glenda_resource_type_t;

// ==========================================
// Generic Protocol (0x000)
// ==========================================
#define GENERIC_REPLY 0x01
#define GENERIC_PING 0x02
#define GENERIC_SHARE_MEMORY 0x03
#define GENERIC_SEND_MESSAGE 0x04

#endif /* GLENDA_PROTOCOL_H */
