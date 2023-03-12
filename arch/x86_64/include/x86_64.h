#ifndef __ARCH_X86_64_X86_64_H__
#define __ARCH_X86_64_X86_64_H__

#include <types.h>

struct segdesc;

static inline void lgdt(struct segdesc *p, uint16_t size) {
  volatile uint16_t pd[5];

  pd[0] = size - 1;
  pd[1] = (uint64_t)p;
  pd[2] = (uint64_t)p >> 16;
  pd[3] = (uint64_t)p >> 32;
  pd[4] = (uint64_t)p >> 48;

  asm volatile("lgdt (%0)" ::"r"(pd));
}

#endif // __ARCH_X86_64_X86_64_H__
