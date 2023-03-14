#include <console.h>
#include <mmu.h>
#include <trap.h>
#include <types.h>

void kernel_main() {

  console_reset();

  printk("Baojuan my voice!");

  printk_color(light_gray, light_blue, "Hello laoli.");

  console_set_color(green, brown);

  seginit();
  idtinit();

  asm volatile("int $64");

  for (;;) {
    ;
  }
}
