#include <vm_map.h>
#include <size.h>

/*  label, ipa, pa, size, attr */
struct memdesc_t vm0_device_md[] = {
    { "sysreg", 0x1C010000, 0x1C010000, SZ_64K, MEMATTR_DEVICE_MEMORY },
    { "sysctl", 0x1C020000, 0x1C020000, SZ_64K, MEMATTR_DEVICE_MEMORY },
    { "aaci", 0x1C040000, 0x1C040000, SZ_64K, MEMATTR_DEVICE_MEMORY },
    { "mmci", 0x1C050000, 0x1C050000, SZ_64K, MEMATTR_DEVICE_MEMORY },
    { "kmi", 0x1C060000, 0x1C060000,  SZ_64K, MEMATTR_DEVICE_MEMORY },
    { "kmi2", 0x1C070000, 0x1C070000, SZ_64K, MEMATTR_DEVICE_MEMORY },
    { "v2m_serial0", 0x1C090000, 0x1C0A0000, SZ_64K, MEMATTR_DEVICE_MEMORY },
    { "v2m_serial1", 0x1C0A0000, 0x1C090000, SZ_64K, MEMATTR_DEVICE_MEMORY },
    { "v2m_serial2", 0x1C0B0000, 0x1C0B0000, SZ_64K, MEMATTR_DEVICE_MEMORY },
    { "v2m_serial3", 0x1C0C0000, 0x1C0C0000, SZ_64K, MEMATTR_DEVICE_MEMORY },
    { "wdt", 0x1C0F0000, 0x1C0F0000, SZ_64K, MEMATTR_DEVICE_MEMORY },
    { "v2m_timer01(sp804)", 0x1C110000, 0x1C110000, SZ_64K, MEMATTR_DEVICE_MEMORY },
    { "v2m_timer23", 0x1C120000, 0x1C120000, SZ_64K, MEMATTR_DEVICE_MEMORY },
    { "rtc", 0x1C170000, 0x1C170000, SZ_64K, MEMATTR_DEVICE_MEMORY },
    { "clcd", 0x1C1F0000, 0x1C1F0000, SZ_64K, MEMATTR_DEVICE_MEMORY },
    {
        "gicc", CFG_GIC_BASE_PA | 0x2000,
        CFG_GIC_BASE_PA | 0x6000, SZ_8K, MEMATTR_DEVICE_MEMORY
    },
    { "SMSC91c111i", 0x1A000000, 0x1A000000, SZ_16M, MEMATTR_DEVICE_MEMORY },
    { "simplebus2", 0x18000000, 0x18000000, SZ_64M, MEMATTR_DEVICE_MEMORY },
    {"start", CFG_GUEST_ATAGS_START_ADDRESS, CFG_MEMMAP_GUEST0_ATAGS_OFFSET, 0x10000000, MEMATTR_NORMAL_WB_CACHEABLE },
    { 0, 0, 0, 0, 0 }
};

struct memdesc_t vm1_device_md[] = {
    { "sysreg", 0x1C010000, 0x1C010000, SZ_64K, MEMATTR_DEVICE_MEMORY },
    { "sysctl", 0x1C020000, 0x1C020000, SZ_64K, MEMATTR_DEVICE_MEMORY },
    { "aaci", 0x1C040000, 0x1C040000, SZ_64K, MEMATTR_DEVICE_MEMORY },
    { "mmci", 0x1C050000, 0x1C050000, SZ_64K, MEMATTR_DEVICE_MEMORY },
    { "kmi", 0x1C060000, 0x1C060000,  SZ_64K, MEMATTR_DEVICE_MEMORY },
    { "kmi2", 0x1C070000, 0x1C070000, SZ_64K, MEMATTR_DEVICE_MEMORY },
    { "v2m_serial0", 0x1C090000, 0x1C0B0000, SZ_64K, MEMATTR_DEVICE_MEMORY },
    { "v2m_serial1", 0x1C0A0000, 0x1C090000, SZ_64K, MEMATTR_DEVICE_MEMORY },
    { "v2m_serial2", 0x1C0B0000, 0x1C0B0000, SZ_64K, MEMATTR_DEVICE_MEMORY },
    { "v2m_serial3", 0x1C0C0000, 0x1C0C0000, SZ_64K, MEMATTR_DEVICE_MEMORY },
    { "wdt", 0x1C0F0000, 0x1C0F0000, SZ_64K, MEMATTR_DEVICE_MEMORY },
    { "v2m_timer01(sp804)", 0x1C110000, 0x1C110000, SZ_64K, MEMATTR_DEVICE_MEMORY },
    { "v2m_timer23", 0x1C120000, 0x1C120000, SZ_64K, MEMATTR_DEVICE_MEMORY },
    { "rtc", 0x1C170000, 0x1C170000, SZ_64K, MEMATTR_DEVICE_MEMORY },
    { "clcd", 0x1C1F0000, 0x1C1F0000, SZ_64K, MEMATTR_DEVICE_MEMORY },
    { "gicc", CFG_GIC_BASE_PA | 0x2000,
        CFG_GIC_BASE_PA | 0x6000, SZ_8K, MEMATTR_DEVICE_MEMORY
    },
    { "SMSC91c111i", 0x1A000000, 0x1A000000, SZ_16M, MEMATTR_DEVICE_MEMORY },
    { "simplebus2", 0x18000000, 0x18000000, SZ_64M, MEMATTR_DEVICE_MEMORY },
    {"start", CFG_GUEST_ATAGS_START_ADDRESS ,CFG_MEMMAP_GUEST1_ATAGS_OFFSET, 0x10000000, MEMATTR_NORMAL_WB_CACHEABLE },

    { 0, 0, 0, 0, 0 }
};

struct memdesc_t vm2_device_md[] = {
    { "sysreg", 0x1C010000, 0x1C010000, SZ_64K, MEMATTR_DEVICE_MEMORY },
    { "sysctl", 0x1C020000, 0x1C020000, SZ_64K, MEMATTR_DEVICE_MEMORY },
    { "aaci", 0x1C040000, 0x1C040000, SZ_64K, MEMATTR_DEVICE_MEMORY },
    { "mmci", 0x1C050000, 0x1C050000, SZ_64K, MEMATTR_DEVICE_MEMORY },
    { "kmi", 0x1C060000, 0x1C060000,  SZ_64K, MEMATTR_DEVICE_MEMORY },
    { "kmi2", 0x1C070000, 0x1C070000, SZ_64K, MEMATTR_DEVICE_MEMORY },
    { "v2m_serial0", 0x1C090000, 0x1C0C0000, SZ_64K, MEMATTR_DEVICE_MEMORY },
    { "v2m_serial1", 0x1C0A0000, 0x1C090000, SZ_64K, MEMATTR_DEVICE_MEMORY },
    { "v2m_serial2", 0x1C0B0000, 0x1C0B0000, SZ_64K, MEMATTR_DEVICE_MEMORY },
    { "v2m_serial3", 0x1C0C0000, 0x1C0C0000, SZ_64K, MEMATTR_DEVICE_MEMORY },
    { "wdt", 0x1C0F0000, 0x1C0F0000, SZ_64K, MEMATTR_DEVICE_MEMORY },
    { "v2m_timer01(sp804)", 0x1C110000, 0x1C110000, SZ_64K, MEMATTR_DEVICE_MEMORY },
    { "v2m_timer23", 0x1C120000, 0x1C120000, SZ_64K, MEMATTR_DEVICE_MEMORY },
    { "rtc", 0x1C170000, 0x1C170000, SZ_64K, MEMATTR_DEVICE_MEMORY },
    { "clcd", 0x1C1F0000, 0x1C1F0000, SZ_64K, MEMATTR_DEVICE_MEMORY },
    {
        "gicc", CFG_GIC_BASE_PA | 0x2000,
        CFG_GIC_BASE_PA | 0x6000, SZ_8K, MEMATTR_DEVICE_MEMORY
    },
    { "SMSC91c111i", 0x1A000000, 0x1A000000, SZ_16M, MEMATTR_DEVICE_MEMORY },
    { "simplebus2", 0x18000000, 0x18000000, SZ_64M, MEMATTR_DEVICE_MEMORY },
    {"start", CFG_GUEST_ATAGS_START_ADDRESS, CFG_MEMMAP_GUEST2_ATAGS_OFFSET, 0x10000000, MEMATTR_NORMAL_WB_CACHEABLE },

    { 0, 0, 0, 0, 0 }
};

struct memdesc_t *vm_mmap[NUM_GUESTS_STATIC];


void setup_vm_mmap(void)
{
    // TODO(wonseok): it will be replaced by DTB.
    vm_mmap[0] = vm0_device_md;
    vm_mmap[1] = vm1_device_md;
    vm_mmap[2] = vm2_device_md;
}
