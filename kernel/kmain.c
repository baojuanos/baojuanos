#include <console.h>
#include <mmu.h>
#include <trap.h>
#include <types.h>

void kernel_main() {

  console_reset();

  for (int i = 0; i < 25; i++) {
    printk("Baojuan my voice! %d\n", i);
  }
  printk("Hello laoli.\n");

  printk("%d\n", 2023);
  printk("0x%x\n", 1024);

  seginit();
  idtinit();

  asm volatile("int $64");

  for (;;) {
    ;
  }
}
