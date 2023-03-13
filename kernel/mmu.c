#include <arch/x86_64/include/x86_64.h>
#include <mmu.h>

struct segdesc gdt[NSEGS];

void seginit() {
  setup_segdesc(&gdt[SEG_KCODE], STA_X, 0);
  setup_segdesc(&gdt[SEG_KDATA], STA_W, 0);
  setup_segdesc(&gdt[SEG_UCODE], STA_X, DPL_USER);
  setup_segdesc(&gdt[SEG_UDATA], STA_W, DPL_USER);

  lgdt(gdt, sizeof(gdt));

  // 此时查看 GDTR 已加载成功
  // (qemu) info registers
  // ...
  // GDT=     ffff800000108000 0000002f
  // ...
  // 对应的描述符也符合预期
  // (qemu) x/6xg 0xffff800000108000
  // ffff800000108000: 0x0000000000000000 0x0020980000000000
  // ffff800000108010: 0x0000920000000000 0x0020f80000000000
  // ffff800000108020: 0x0000f20000000000 0x0000000000000000
}

void setup_segdesc(struct segdesc *d, uint8_t type, uint8_t dpl) {
  d->type = type;
  d->dpl = dpl;
  d->s = 1;
  d->p = 1;

  // 如果是代码段则置位 l 位, 表示 64 位代码段
  if ((type & STA_X) == STA_X) {
    d->l = 1;
  }
}
