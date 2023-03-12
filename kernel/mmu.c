#include <arch/x86_64/include/x86_64.h>
#include <mmu.h>

struct segdesc gdt[NSEGS];

void seginit() {
  setup_segdesc(&gdt[SEG_KCODE], STA_X, 0);
  setup_segdesc(&gdt[SEG_KDATA], STA_W, 0);
  setup_segdesc(&gdt[SEG_UCODE], STA_X, DPL_USER);
  setup_segdesc(&gdt[SEG_UDATA], STA_W, DPL_USER);

  lgdt(gdt, sizeof(gdt));
}

void setup_segdesc(struct segdesc *d, uint8_t type, uint8_t dpl) {
  d->type = type;
  d->dpl = dpl;
  d->s = 1;
  d->p = 1;

  // 如果是代码段则置位 l 位
  if ((type & STA_X) == STA_X) {
    d->l = 1;
  }
}
