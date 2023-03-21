#ifndef __MULTIBOOT_HEADER__
#define __MULTIBOOT_HEADER__

#define MULTIBOOT2_HEADER_MAGIC      0xE85250D6
#define MULTIBOOT2_BOOTLOADER_MAGIC  0x36d76289
#define MULTIBOOT2_ARCHITECTURE_I386 0

#define MULTIBOOT_TAG_ALIGN                 8
#define MULTIBOOT_TAG_TYPE_END              0
#define MULTIBOOT_TAG_TYPE_CMDLINE          1
#define MULTIBOOT_TAG_TYPE_BOOT_LOADER_NAME 2
#define MULTIBOOT_TAG_TYPE_MODULE           3
#define MULTIBOOT_TAG_TYPE_BASIC_MEMINFO    4
#define MULTIBOOT_TAG_TYPE_BOOTDEV          5
#define MULTIBOOT_TAG_TYPE_MMAP             6
#define MULTIBOOT_TAG_TYPE_VBE              7
#define MULTIBOOT_TAG_TYPE_FRAMEBUFFER      8
#define MULTIBOOT_TAG_TYPE_ELF_SECTIONS     9
#define MULTIBOOT_TAG_TYPE_APM              10
#define MULTIBOOT_TAG_TYPE_EFI32            11
#define MULTIBOOT_TAG_TYPE_EFI64            12
#define MULTIBOOT_TAG_TYPE_SMBIOS           13
#define MULTIBOOT_TAG_TYPE_ACPI_OLD         14
#define MULTIBOOT_TAG_TYPE_ACPI_NEW         15
#define MULTIBOOT_TAG_TYPE_NETWORK          16
#define MULTIBOOT_TAG_TYPE_EFI_MMAP         17
#define MULTIBOOT_TAG_TYPE_EFI_BS           18
#define MULTIBOOT_TAG_TYPE_EFI32_IH         19
#define MULTIBOOT_TAG_TYPE_EFI64_IH         20
#define MULTIBOOT_TAG_TYPE_LOAD_BASE_ADDR   21

#ifndef __ASSEMBLER__
#include <types.h>

struct multiboot_tag_t {
  uint32_t type;
  uint32_t size;
};

struct multiboot_memory_map_t {
  uint64_t addr;
  uint64_t len;
#define MULTIBOOT_MEMORY_AVAILABLE        1
#define MULTIBOOT_MEMORY_RESERVED         2
#define MULTIBOOT_MEMORY_ACPI_RECLAIMABLE 3
#define MULTIBOOT_MEMORY_NVS              4
#define MULTIBOOT_MEMORY_BADRAM           5
  uint32_t type;
  uint32_t zero;
};

struct multiboot_tag_mmap_t {
  uint32_t type;
  uint32_t size;
  uint32_t entry_size;
  uint32_t entry_version;
  struct multiboot_memory_map_t entries[0];
};

char *multiboot_tag_type_desc[] = {
    [MULTIBOOT_TAG_TYPE_END]              = "end",
    [MULTIBOOT_TAG_TYPE_CMDLINE]          = "cmdline",
    [MULTIBOOT_TAG_TYPE_BOOT_LOADER_NAME] = "boot_loader_name",
    [MULTIBOOT_TAG_TYPE_MODULE]           = "module",
    [MULTIBOOT_TAG_TYPE_BASIC_MEMINFO]    = "basic_meminfo",
    [MULTIBOOT_TAG_TYPE_BOOTDEV]          = "bootdev",
    [MULTIBOOT_TAG_TYPE_MMAP]             = "mmap",
    [MULTIBOOT_TAG_TYPE_VBE]              = "vbe",
    [MULTIBOOT_TAG_TYPE_FRAMEBUFFER]      = "framebuffer",
    [MULTIBOOT_TAG_TYPE_ELF_SECTIONS]     = "elf_sections",
    [MULTIBOOT_TAG_TYPE_APM]              = "apm",
    [MULTIBOOT_TAG_TYPE_EFI32]            = "efi32",
    [MULTIBOOT_TAG_TYPE_EFI64]            = "efi64",
    [MULTIBOOT_TAG_TYPE_SMBIOS]           = "smbios",
    [MULTIBOOT_TAG_TYPE_ACPI_OLD]         = "acpi_old",
    [MULTIBOOT_TAG_TYPE_ACPI_NEW]         = "acpi_new",
    [MULTIBOOT_TAG_TYPE_NETWORK]          = "network",
    [MULTIBOOT_TAG_TYPE_EFI_MMAP]         = "efi_mmap",
    [MULTIBOOT_TAG_TYPE_EFI_BS]           = "efi_bs",
    [MULTIBOOT_TAG_TYPE_EFI32_IH]         = "efi32_ih",
    [MULTIBOOT_TAG_TYPE_EFI64_IH]         = "efi64_ih",
    [MULTIBOOT_TAG_TYPE_LOAD_BASE_ADDR]   = "load_base_addr",
};

#endif // __ASSEMBLER__

#endif // __MULTIBOOT_HEADER__
