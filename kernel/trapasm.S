.global trap_dispatcher
.global trapentry
trapentry:
  // System V ABI x64 调用规范
  // 前六个参数依次传入 rdi, rsi, rdx, rcx, r8, r9
  // 这里将当前栈的地址作为参数传给 trap_dispatcher
  movq %rsp, %rdi
  call trap_dispatcher

.global trapret
trapret:
  // 弹出 trapno 和 errcode，处理器不会弹出错误码，需要手动弹出
  addq $0x10, %rsp

  // 这里要加操作数位宽的后缀，iret 的指令码是 cc，iretq 的指令码是 48 cf
  // 48 对应 REX.W 指令前缀
  // In 64-bit mode, the instruction’s default operation size is 32 bits. 
  // Use of the REX.W prefix promotes operation to 64 bits (IRETQ)
  // 详细解释见 intel 开发文档 
  // Volume 2 (2A, 2B, 2C & 2D):Instruction Set Reference, A-Z -> Chapter 2 Instruction Format -> 2.2 IA-32e Mode -> 2.2.1 REX Prefixes
  iretq
