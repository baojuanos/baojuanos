#ifndef __KERNEL_H__
#define __KERNEL_H__

#define KERNEL_BASE 0xffff800000000000

#ifndef __ASSEMBLER__

// linker script 中提供的内核代码段、数据段及内核结束地址处的符号
extern uint8_t etext;
extern uint8_t edata;
extern uint8_t end;

#endif // __ASSEMBLER__

#endif // __KERNEL_H__
