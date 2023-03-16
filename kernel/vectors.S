.global trapentry

// 使用 .macro 和 .rept 批量设置 256 个中断处理程序入口地址
.section .text

.altmacro

.macro isr n
  .global isr\n
  isr\n:
    // 如果中断没有错误码则手动压入 0，保持异常栈帧结构一致
    .if (!(\n == 8 || (\n >= 10 && \n <= 14) || \n == 17))
      pushq $0
    .endif
    pushq $\n
    jmp trapentry
.endm

.set i, 0
.rept 256
  isr %i
  .set i, i + 1
.endr

.section .data
.global vectors
vectors:

.macro addr n
  .quad isr\n
.endm

.set i, 0
.rept 256
  addr %i
  .set i, i + 1
.endr
