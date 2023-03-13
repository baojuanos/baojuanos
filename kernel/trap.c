#include <console.h>
#include <mmu.h>
#include <trap.h>
#include <x86_64.h>

struct gatedesc idt[NINTERS];

// 默认中断处理方法
void default_interrupt_handler() {

  printk("interrupt is handling...");

  for (;;) {
    ;
  }
};

// 设置并加载 IDT
void idtinit() {
  for (int i = 0; i < NINTERS; i++) {
    setup_gatedesc(&idt[i], SEG_KCODE << 3, (uint64_t)default_interrupt_handler, STS_IG64, 0);
  }

  lidt(idt, sizeof(idt));
}

void setup_gatedesc(struct gatedesc *d, uint16_t cs, uint64_t offset, uint8_t type, uint8_t dpl) {
  d->cs = cs;
  d->off_15_0 = (uint16_t)(offset & 0xffff);
  d->off_31_16 = (uint16_t)((offset >> 16) & 0xffff);
  d->off_63_32 = (uint32_t)(offset >> 32);
  d->type = type;
  d->dpl = dpl;
  d->ist = 0;
  d->zero0 = 0;
  d->zero1 = 0;
  d->p = 1;
  d->rsv0 = 0;
}
