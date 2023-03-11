#include <multiboot2.h>

#define STACK_SIZE 0x4000 // 16KB

.set header_hength, multiboot_header_end - multiboot_header
.set checksum, -(MULTIBOOT2_HEADER_MAGIC + MULTIBOOT_ARCHITECTURE_I386 + header_hength)

.global _start

.section ".bstext", "ax"
multiboot_header:
.long MULTIBOOT2_HEADER_MAGIC     # magic
.long MULTIBOOT_ARCHITECTURE_I386 # architecture, 32-bit (protected) mode of i386
.long header_hength               # header length
.long checksum                    # checksum

multiboot_header_tag_end:
.short 0
.short 0
.long  8
multiboot_header_end:

.code32
_start:
cli

movb $'3', 0xb8000
movb $0x0a, 0xb8001
movb $'2', 0xb8002
movb $0x0a, 0xb8003

movb $'-', 0xb8004
movb $0x04, 0xb8005
movb $'>', 0xb8006
movb $0x04, 0xb8007

# 开启 PAE
movl %cr4, %eax
bts $5, %eax
movl %eax, %cr4

# 加载 cr3
movl $pml4e, %eax
movl %eax, %cr3

# 开启 long mode
movl $0xc0000080, %ecx
rdmsr
bts $8, %eax
wrmsr

# 开启 PE PG
movl %cr0, %eax
bts $0, %eax
bts $31, %eax
movl %eax, %cr0

lgdt gdt64_desc

ljmp $0x08, $_start64

hlt

.code64
_start64:
movw $0x10, %ax
movw %ax, %ds
movw %ax, %es
movw %ax, %fs
movw %ax, %gs
movw %ax, %ss

movb $'6', 0xb8008
movb $0x0b, 0xb8009
movb $'4', 0xb800a
movb $0x0b, 0xb800b

// 初始化栈指针
// movq $(stack + STACK_SIZE), %rsp

movabsq $(stack + STACK_SIZE), %rsp

// 我最理想的写法是通过 callq 直接跳转到高地址空间的 kernel_main
// 即加上 KERNEL_BASE = 0xffff800000000000 之后的地址处
// 这种写法在这里链接时会报 relocation R_X86_64_32 out of range 的错误
// 初始化栈指针最初使用的 movq $(stack + STACK_SIZE), %rsp 也会报类似的错
// 关于此错误可以看这里的解释 https://stackoverflow.com/questions/6093547/what-do-r-x86-64-32s-and-r-x86-64-64-relocation-mean

// 当然如果把 KERNEL_BASE 调整为 0xffffffff80000000 使用 callq kernel_main 也可以通过编译
// callq kernel_main

// movq $0xffff800000109000, %rsp

// hlt

// movq $0xffff800000105060, %rax

// 这里最终采用的方案是使用 movabs + jmp 指令间接跳转到内核主函数
// 在64位代码中, movabs 可用于编码带有 64位 位移或立即操作数的 mov 指令 https://sourceware.org/binutils/docs/as/i386_002dVariations.html
// 查看 movabs 编译后生成的重定位信息如下:
// $ objdump -drz -Msuffix arch/x86_64/boot.o
// ...
//  b3:   c6 04 25 0b 80 0b 00    movb   $0xb,0xb800b
//  ba:   0b 
//  bb:   48 bc 00 00 00 00 00    movabsq $0x0,%rsp
//  c2:   00 00 00 
//                        bd: R_X86_64_64 stack+0x4000
//  c5:   48 b8 00 00 00 00 00    movabsq $0x0,%rax
//  cc:   00 00 00 
//                        c7: R_X86_64_64 kernel_main
//  cf:   ff e0                   jmpq   *%rax
//  d1:   f4                      hlt
// ...
// 可以看到 stack 和 kernel_main 的重定位类型已经变为 R_X86_64_64
movabsq $kernel_main, %rax
jmpq *%rax

// 也可以采用手动压栈代码段选择子和指令地址 + lret 模拟过程调用返回的方式跳转到内核主函数
// pushq $0x8
// pushq %rax

// lretq

// callq 0xffff800000105060

hlt

.section ".bsdata", "a"
.align 8
gdt64:
gdt64_null:
  .quad 0x0000000000000000
gdt64_code64:
  .quad 0x0020980000000000
gdt64_data64:
  .quad 0x0000920000000000

gdt64_desc:
  .word . - gdt64 - 1
  .long gdt64

// 临时页表设置移入 entry.c 文件，使用 c 语言重写，使结构更清晰
// .p2align 12
// pml4e:
//   .quad pdpte + 7
//   .fill 511, 8, 0
// pdpte:
//   .quad pde + 3
//   .fill 511, 8, 0
// pde:
//   .quad	0x000083
// 	.quad	0x200083
// 	.quad	0x400083
// 	.quad	0x600083
// 	.quad	0x800083
//   .fill 507, 8, 0

.comm stack, STACK_SIZE
