#include <console.h>
#include <mmu.h>
#include <trap.h>
#include <x86_64.h>

// 中断描述符表
struct gatedesc idt[NINTERS];

// 中断处理程序入口地址构成的数组 (在 vectors.S 中)
extern uint64_t vectors[];

// 默认中断处理方法
void default_interrupt_handler() {

  printk("interrupt is handling...");

  for (;;) {
    ;
  }
};

// 中断处理入口
void trap_dispatcher(struct trapframe *tf) {
  printk("trapframe: 0x%p, trapno: %d err: %d\n", tf, tf->trapno, tf->err);
}

// 设置并加载 IDT
void idtinit() {
  for (int i = 0; i < NINTERS; i++) {
    setup_gatedesc(&idt[i], SEG_KCODE << 3, vectors[i], STS_IG64, 0);
  }

  lidt(idt, sizeof(idt));
}

void setup_gatedesc(struct gatedesc *d, uint16_t cs, uint64_t offset, uint8_t type, uint8_t dpl) {
  d->cs        = cs;
  d->off_15_0  = (uint16_t)(offset & 0xffff);
  d->off_31_16 = (uint16_t)((offset >> 16) & 0xffff);
  d->off_63_32 = (uint32_t)(offset >> 32);
  d->type      = type;
  d->dpl       = dpl;
  d->ist       = 0;
  d->zero0     = 0;
  d->zero1     = 0;
  d->p         = 1;
  d->rsv0      = 0;
}
