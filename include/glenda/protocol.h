#ifndef GLENDA_PROTOCOL_H
#define GLENDA_PROTOCOL_H

// Core Protocols
#define PROTO_GENERIC 0x0000
#define PROTO_KERNEL 0x0100
#define PROTO_PROCESS 0x0200
#define PROTO_DEVICE 0x0300
#define PROTO_INIT 0x0400
#define PROTO_FS 0x0500
#define PROTO_NETWORK 0x0600

// ==========================================
// FS Protocol (0x500)
// ==========================================

// Namespace Operations
#define FS_OPEN 1
#define FS_MKDIR 2
#define FS_UNLINK 3
#define FS_RENAME 4
#define FS_STAT_PATH 5

// File Handle Operations
#define FS_READ 10
#define FS_WRITE 11
#define FS_CLOSE 12
#define FS_STAT 13
#define FS_GETDENTS 14
#define FS_SEEK 15
#define FS_SYNC 16
#define FS_TRUNCATE 17

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
#define PROC_SPAWN 1
#define PROC_EXIT 2
#define PROC_WAIT 3
#define PROC_KILL 4
#define PROC_FORK 5

#define PROC_SBRK 6
#define PROC_MMAP 7
#define PROC_MUNMAP 8

#define PROC_THREAD_CREATE 9
#define PROC_THREAD_EXIT 10
#define PROC_THREAD_JOIN 11
#define PROC_FUTEX_WAIT 12
#define PROC_FUTEX_WAKE 13
#define PROC_YIELD 14
#define PROC_SLEEP 15

#define PROC_GET_PID 16
#define PROC_PS 17
#define PROC_INIT 99

// ==========================================
// Device Protocol (0x300)
// ==========================================
#define PROTO_DEVICE_PCI 0x301
#define PROTO_DEVICE_IOMMU 0x302
#define PROTO_DEVICE_UART 0x303

// UART Methods
#define UART_PUT_CHAR 1
#define UART_GET_CHAR 2
#define UART_PUT_STR 3
#define UART_SET_BAUD 4

// ==========================================
// Init Protocol (0x400)
// ==========================================
#define INIT_SERVICE_START 1
#define INIT_SERVICE_STOP 2
#define INIT_SERVICE_RESTART 3
#define INIT_SERVICE_RELOAD 4
#define INIT_SERVICE_QUERY 5
#define INIT_GET_CAP 6
#define INIT_GET_RESOURCE 7

// Init Capabilities
#define INIT_CAP_CONSOLE 1
#define INIT_CAP_INITRD 2
#define INIT_CAP_UNTYPED 3
#define INIT_CAP_MMIO 4
#define INIT_CAP_IRQ 5

// Init Resources
#define INIT_RESOURCE_BOOT_ARGS 1
#define INIT_RESOURCE_PLATFORM_INFO 2

// ==========================================
// Kernel / Fault Protocol (0x100)
// ==========================================
// These are often delivered as IPC messages to fault handlers
#define FAULT_SYSCALL 1
#define FAULT_PAGE_FAULT 2
#define FAULT_ILLEGAL_INSTRUCTION 3
#define FAULT_BREAKPOINT 4
#define FAULT_ACCESS_FAULT 5
#define FAULT_ACCESS_MISALIGNED 6
#define FAULT_UNKNOWN_FAULT 7
#define FAULT_IRQ 8

#endif
