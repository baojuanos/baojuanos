#include <multiboot2.h>

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

.p2align 12
pml4e:
  .quad pdpte + 7
  .fill 511, 8, 0
pdpte:
  .quad pde + 3
  .fill 511, 8, 0
pde:
  .quad	0x000083
	.quad	0x200083
	.quad	0x400083
	.quad	0x600083
	.quad	0x800083
  .fill 507, 8, 0
