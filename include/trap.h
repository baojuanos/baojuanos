#ifndef __TRAP_H__
#define __TRAP_H__

#include <types.h>

// 系统支持的中断数量
#define NINTERS 256

// 系统段 type
#define STS_T64A 0x9 // 可用 64位 TSS
#define STS_IG64 0xE // 64位 中断门
#define STS_TG64 0xF // 64位 陷阱门

// 64 位 IDT 门描述符
struct gatedesc {
  uint32_t off_15_0 : 16;
  uint32_t cs : 16;
  uint32_t ist : 3;
  uint32_t zero0 : 5;
  uint32_t type : 4;
  uint32_t zero1 : 1;
  uint32_t dpl : 2;
  uint32_t p : 1;
  uint32_t off_31_16 : 16;
  uint32_t off_63_32 : 32;
  uint32_t rsv0 : 32;
};

void setup_gatedesc(struct gatedesc *d, uint16_t cs, uint64_t offset, uint8_t type, uint8_t dpl);

void idtinit();

#endif // __TRAP_H__
