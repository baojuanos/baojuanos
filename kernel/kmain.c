#include <console.h>
#include <mmu.h>
#include <trap.h>
#include <types.h>

void kernel_main() {

  printk("Baojuan my voice!");

  seginit();
  idtinit();

  asm volatile("int $64");

  for (;;) {
    ;
  }
}
