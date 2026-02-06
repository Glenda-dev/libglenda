#ifndef GLENDA_PLATFORM_H
#define GLENDA_PLATFORM_H

#include <glenda/stdint.h>
#include <glenda/stddef.h>

#define MAX_MEMORY_REGIONS 16
#define MAX_DEVICES 64

typedef enum {
    MEMORY_TYPE_RAM = 1,
    MEMORY_TYPE_MMIO = 2,
    MEMORY_TYPE_RESERVED = 3
} glenda_memory_type_t;

typedef enum {
    DEVICE_KIND_UNKNOWN = 0,
    DEVICE_KIND_UART = 1,
    DEVICE_KIND_INTC = 2,
    DEVICE_KIND_TIMER = 3,
    DEVICE_KIND_VIRTIO = 4,
    DEVICE_KIND_PCI_HOST = 5
} glenda_device_kind_t;

typedef enum {
    BUS_TYPE_SYSTEM = 0,
    BUS_TYPE_PCI = 1,
    BUS_TYPE_USB = 2,
    BUS_TYPE_PLATFORM = 3
} glenda_bus_type_t;

typedef struct {
    size_t start;
    size_t size;
    uint32_t region_type;
} glenda_memory_region_t;

typedef struct {
    uint8_t compatible[64];
    size_t base_addr;
    size_t size;
    uint32_t irq;
    uint32_t kind;
    uint32_t parent_index;
    uint32_t bus_type;
} glenda_device_desc_t;

typedef struct {
    uint8_t model_name[64];
    uint8_t arch[16];
    uint8_t bootargs[256];
    glenda_memory_region_t initrd;
    size_t cpu_count;
    size_t clock_freq;
    size_t irq_count;
    glenda_memory_region_t memory_regions[MAX_MEMORY_REGIONS];
    size_t memory_region_count;
    glenda_device_desc_t devices[MAX_DEVICES];
    size_t device_count;
} glenda_platform_info_t;

#define GLENDA_PLATFORM_INFO_SIZE sizeof(glenda_platform_info_t)

#endif /* GLENDA_PLATFORM_H */
