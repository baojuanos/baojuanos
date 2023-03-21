#ifndef __MMU_H__
#define __MMU_H__

#include <types.h>

// 段选择子
#define SEG_KCODE 1 // 内核代码段
#define SEG_KDATA 2 // 内核数据+堆栈段
#define SEG_UCODE 3 // 用户代码段
#define SEG_UDATA 4 // 用户数据+堆栈段
#define SEG_TSS   5 // 任务状态段

// 段数量
#define NSEGS 6

// ia-32e 模式段描述符只有少数标志位有效
struct segdesc {
  uint64_t rsv0 : 40;
  uint64_t type : 4;
  uint64_t s : 1;
  uint64_t dpl : 2;
  uint64_t p : 1;
  uint64_t rsv1 : 5;
  uint64_t l : 1;
  uint64_t db : 1;
  uint64_t rsv2 : 9;
};

// 用户 DPL
#define DPL_USER 0x3

// 应用段 type 位
#define STA_X 0x8 // 可执行段
#define STA_W 0x2 // 可写段(不可执行)
#define STA_R 0x2 // 可读段(可执行)

void setup_segdesc(struct segdesc *d, uint8_t type, uint8_t dpl);

void seginit();

#endif // __MMU_H__
