#ifndef __ARCH_X86_64_X86_64_H__
#define __ARCH_X86_64_X86_64_H__

#include <types.h>

struct segdesc;

// 伪描述符, 用于保存 GDTR IDTR 这种结构
struct pseudo_desc {
  uint16_t limit;
  uint64_t base;
} __attribute__((__packed__));

static inline void lgdt(struct segdesc *p, uint16_t size) {

  struct pseudo_desc pd = {
      .limit = size - 1,
      .base = (uint64_t)p,
  };

  asm volatile("lgdt (%0)" ::"r"(&pd));
}

#endif // __ARCH_X86_64_X86_64_H__
