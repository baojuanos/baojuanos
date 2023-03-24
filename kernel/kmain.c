#include <console.h>
#include <kernel.h>
#include <mmu.h>
#include <multiboot2.h>
#include <stddef.h>
#include <trap.h>
#include <types.h>

void kernel_main(uint32_t mbi_magic, uint64_t mbi_addr) {

  console_reset();

  if (mbi_magic != MULTIBOOT2_BOOTLOADER_MAGIC) {
    printk("invalid mbi magic: 0x%x\n", mbi_magic);
    return;
  }

  printk("mbi addr: 0x%p\n\n", mbi_addr);

  if (mbi_addr & 7) {
    printk("unaligned mbi\n");
    return;
  }

  printk("kernel:\n");
  printk(" &etext = 0x%x\n", &etext);
  printk(" &edata = 0x%x\n", &edata);
  printk(" &end   = 0x%x\n\n", &end);

  for (struct multiboot_tag_t *tag = (struct multiboot_tag_t *)(mbi_addr + 8);
       tag->type != MULTIBOOT_TAG_TYPE_END;
       tag = (struct multiboot_tag_t *)((uint8_t *)tag + ((tag->size + 7) & ~7))) {

    // printk("Tag type: 0x%x, size: 0x%x, name: %s\n", tag->type, tag->size,
    //        multiboot_tag_type_desc[tag->type]);

    if (tag->type != MULTIBOOT_TAG_TYPE_MMAP) {
      continue;
    }

    printk("mmap:\n");

    struct multiboot_tag_mmap_t *mmap_tag = (struct multiboot_tag_mmap_t *)tag;

    for (struct multiboot_memory_map_t *mmap = mmap_tag->entries;
         (uint8_t *)mmap < (uint8_t *)mmap_tag + mmap_tag->size;
         mmap = (struct multiboot_memory_map_t *)((uint64_t)mmap + mmap_tag->entry_size)) {
      printk(" base_addr = 0x%x, length = 0x%x, type = 0x%x\n", mmap->addr, mmap->len, mmap->type);
    }
  }

  seginit();
  idtinit();

  // asm volatile("int $64");
}
