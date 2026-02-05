#ifndef GLENDA_H
#define GLENDA_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define PGSIZE 4096
#define VA_MAX (1UL << 63)
#define EMPTY_VA 0
#define VPN_MASK 0
#define USER_VA 65536
#define KSTACK_PAGES 1

#define SEND 1
#define RECV 2
#define CALL 3
#define NOTIFY 4
#define REPLY 1

#define PGSIZE 4096

#define VA_MAX (1UL << 63)

#define EMPTY_VA 0

#define VPN_MASK 0

#define USER_VA 65536

#define KSTACK_PAGES 1

#define CNODE_BITS 8

#define CNODE_SIZE ((SLOT_SIZE * (1 << CNODE_BITS)) + 8)

#define CNODE_PAGES (((CNODE_SIZE + PGSIZE) - 1) / PGSIZE)

#define CNODE_SLOTS (1 << CNODE_BITS)

#define CNODE_MASK (CNODE_SLOTS - 1)

#define CONFIGURE 1

#define SET_PRIORITY 2

#define SET_ENTRYPOINT 3

#define SET_FAULT_HANDLER 4

#define SET_AFFINITY 5

#define SET_REGISTERS 6

#define RESUME 7

#define SUSPEND 8

#define MAP_TABLE 1

#define MINT 1

#define COPY 2

#define DELETE 3

#define REVOKE 4

#define DEBUG_PRINT 5

#define RETYPE 1

#define SET_NOTIFICATION 1

#define ACK 2

#define CLEAR_NOTIFICATION 3

#define CONSOLE_PUT_STR 1

#define CONSOLE_GET_CHAR 2

#define CONSOLE_GET_STR 3

#define SHELL 4

#define MAP 1

#define UNMAP 2

#define SETUP 4

#define HEAP_PAGES 256

#define HEAP_SIZE (HEAP_PAGES * PGSIZE)

#define HEAP_VA 536870912UL

#define BUFFER_MAX_SIZE (3 * 1024)

#define MAX_MRS 8

#define TRAMPOLINE_VA (VA_MAX - PGSIZE)

#define TRAPFRAME_VA (TRAMPOLINE_VA - PGSIZE)

#define UTCB_VA (TRAPFRAME_VA - PGSIZE)

#define STACK_VA (UTCB_VA - PGSIZE)

#define ENTRY_VA USER_VA

#define BOOTINFO_VA 1073741824UL

#define INITRD_VA 1342177280UL

#define NETWORK_PROTO 1536

#define FS_PROTO 1280

#define INIT_PROTOCOL 1024

#define DEVICE_PROTO 768

#define PROCESS_PROTO 512

#define KERNEL_PROTO 256

#define GENERIC_PROTO 0

#define PCI_PROTO 769

#define IOMMU_PROTO 770

#define UART_PROTO 771

#define BLOCK_PROTO 772

#define NET_PROTO 773

#define IB_PROTO 774

#define WIFI_PROTO 775

#define INPUT_PROTO 776

#define FB_PROTO 777

#define USB_PROTO 778

#define SPI_PROTO 779

#define I2C_PROTO 780

#define GPIO_PROTO 781

#define RNG_PROTO 782

#define SCAN_PLATFORM 1

#define GET_NODE 2

#define FIND_COMPATIBLE 3

#define INIT_MANIFEST 4

#define GET_DEVICE_BY_NAME 5

#define GET_INFO 10

#define MAP_MMIO 11

#define GET_IRQ 12

#define ALLOC_DMA 13

#define BUS_PCI 1

#define BUS_PLATFORM 2

#define GET_CAPACITY 1

#define GET_BLOCK_SIZE 2

#define READ_BLOCKS 3

#define WRITE_BLOCKS 4

#define SYNC 5

#define FLUSH 2

#define SET_MODE 1

#define WRITE 2

#define READ 3

#define MODE_INPUT 0

#define MODE_OUTPUT 1

#define MODE_ALT 2

#define WRITE_READ 3

#define I2C_ADDR_10BIT 32768

#define READ_EVENT 1

#define EV_SYN 0

#define EV_KEY 1

#define EV_REL 2

#define EV_ABS 3

#define REL_X 0

#define REL_Y 1

#define REL_WHEEL 8

#define IOMMU_READ (1 << 0)

#define IOMMU_WRITE (1 << 1)

#define IOMMU_EXEC (1 << 2)

#define IOMMU_CACHE (1 << 3)

#define GET_MAC 1

#define SETUP_RX_RING 4

#define SETUP_TX_RING 5

#define READ_CONFIG 1

#define WRITE_CONFIG 2

#define ENABLE_BUS_MASTER 3

#define ENABLE_MSI 4

#define PCI_VENDOR_ID 0

#define PCI_DEVICE_ID 2

#define PCI_COMMAND 4

#define PCI_STATUS 6

#define PCI_CLASS_REV 8

#define PCI_HEADER_TYPE 14

#define PCI_BAR0 16

#define PCI_CAPABILITY_LIST 52

#define PCI_CMD_IO 1

#define PCI_CMD_MEM 2

#define PCI_CMD_BUS_MASTER 4

#define PCI_CMD_INTX_DISABLE 1024

#define READ_RANDOM 1

#define TRANSFER 1

#define CONFIG 2

#define MODE_0 0

#define MODE_1 1

#define MODE_2 2

#define MODE_3 3

#define PUT_CHAR 1

#define GET_CHAR 2

#define PUT_STR 3

#define SET_BAUD_RATE 4

#define RESET_PORT 1

#define CONTROL_XFER 2

#define BULK_XFER 3

#define INTR_XFER 4

#define REQ_DIR_OUT 0

#define REQ_DIR_IN 128

#define REQ_TYPE_STANDARD 0

#define REQ_TYPE_CLASS 32

#define REQ_TYPE_VENDOR 64

#define REQ_RECIP_DEVICE 0

#define REQ_RECIP_INTERFACE 1

#define REQ_RECIP_ENDPOINT 2

#define REQ_GET_STATUS 0

#define REQ_CLEAR_FEATURE 1

#define REQ_SET_ADDRESS 5

#define REQ_GET_DESCRIPTOR 6

#define REQ_SET_DESCRIPTOR 7

#define REQ_GET_CONFIGURATION 8

#define REQ_SET_CONFIGURATION 9

#define DESC_DEVICE 1

#define DESC_CONFIGURATION 2

#define DESC_STRING 3

#define DESC_INTERFACE 4

#define DESC_ENDPOINT 5

#define EP_ATTR_CONTROL 0

#define EP_ATTR_ISOCH 1

#define EP_ATTR_BULK 2

#define EP_ATTR_INTR 3

#define SCAN 1

#define GET_SCAN_RESULTS 2

#define CONNECT 3

#define DISCONNECT 4

#define GET_STATUS 5

#define SEC_OPEN 0

#define SEC_WEP 1

#define SEC_WPA2 2

#define SEC_WPA3 3

#define STATUS_DISCONNECTED 0

#define STATUS_CONNECTING 1

#define STATUS_CONNECTED 2

#define STATUS_FAILED 3

#define PROTOCOL_ID 1280

#define OPEN 1

#define MKDIR 2

#define UNLINK 3

#define RENAME 4

#define STAT_PATH 5

#define CLOSE 12

#define STAT 13

#define GETDENTS 14

#define SEEK 15

#define TRUNCATE 17

#define SEEK_SET 0

#define SEEK_CUR 1

#define SEEK_END 2

#define SERVICE_START 1

#define SERVICE_STOP 2

#define SERVICE_RESTART 3

#define SERVICE_RELOAD 4

#define SERVICE_QUERY 5

#define SYSCALL 1

#define PAGE_FAULT 2

#define ILLEGAL_INSTRUCTION 3

#define BREAKPOINT 4

#define ACCESS_FAULT 5

#define ACCESS_MISALIGNED 6

#define UNKNOWN_FAULT 7

#define IRQ 8

#define SOCKET 1

#define BIND 10

#define LISTEN 11

#define ACCEPT 12

#define GET_SOCKNAME 17

#define GET_PEERNAME 18

#define SET_SOCKOPT 19

#define GET_SOCKOPT 20

#define AF_INET 2

#define AF_INET6 10

#define SOCK_STREAM 1

#define SOCK_DGRAM 2

#define SOCK_RAW 3

#define IPPROTO_IP 0

#define IPPROTO_ICMP 1

#define IPPROTO_TCP 6

#define IPPROTO_UDP 17

#define IPPROTO_IPV6 41

#define IPPROTO_RAW 255

#define SPAWN 1

#define EXIT 2

#define WAIT 3

#define KILL 4

#define FORK 5

#define SBRK 6

#define MMAP 7

#define MUNMAP 8

#define THREAD_CREATE 9

#define THREAD_EXIT 10

#define THREAD_JOIN 11

#define FUTEX_WAIT 12

#define FUTEX_WAKE 13

#define YIELD 14

#define SLEEP 15

#define GET_PID 16

#define PS 17

#define INIT 99

#define BOOTINFO_MAGIC 2576980377

#define BOOTINFO_SIZE PGSIZE

#define MAX_UNTYPED_REGIONS 8

#define MAX_MMIO_REGIONS 64

#define MAX_MEMORY_REGIONS 16

#define MAX_DEVICES 64

#define PLATFORM_INFO_PAGES (((PLATFORM_INFO_SIZE + PGSIZE) - 1) / PGSIZE)

#endif /* GLENDA_H */
