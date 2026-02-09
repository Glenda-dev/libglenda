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

// ==========================================
// FS Protocol (0x500)
// ==========================================

// Namespace Operations
#define FS_OPEN 0x01
#define FS_MKDIR 0x02
#define FS_UNLINK 0x03
#define FS_RENAME 0x04
#define FS_STAT_PATH 0x05

// File Handle Operations
#define FS_READ 0x10
#define FS_WRITE 0x11
#define FS_CLOSE 0x12
#define FS_STAT 0x13
#define FS_GETDENTS 0x14
#define FS_SEEK 0x15
#define FS_SYNC 0x16
#define FS_TRUNCATE 0x17
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
// Device Protocol (0x300)
// ==========================================
#define PROTO_DEVICE_PCI 0x301
#define PROTO_DEVICE_IOMMU 0x302
#define PROTO_DEVICE_UART 0x303

// UART Methods
#define UART_PUT_CHAR 0x01
#define UART_GET_CHAR 0x02
#define UART_PUT_STR 0x03
#define UART_SET_BAUD 0x04

// ==========================================
// Init Protocol (0x400)
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

#endif

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
// Resource Protocol (0x300)
// ==========================================
#define RESOURCE_ALLOCATE 0x01
#define RESOURCE_FREE 0x02
#define RESOURCE_GETRESOURCE 0x03
#define RESOURCE_GETCAP 0x04
#define RESOURCE_MAP 0x10
#define RESOURCE_UNMAP 0x11
#define RESOURCE_CLONE 0x12
#define RESOURCE_MMAP 0x13
#define RESOURCE_MUNMAP 0x14
#define RESOURCE_SBRK 0x15

// ==========================================
// Generic Protocol (0x000)
// ==========================================
#define GENERIC_REPLY 0x01
#define GENERIC_PING 0x02
#define GENERIC_SHARE_MEMORY 0x03
#define GENERIC_SEND_MESSAGE 0x04