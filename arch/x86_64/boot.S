#include <multiboot2.h>

.set header_hength, multiboot_header_end - multiboot_header
.set checksum, -(MULTIBOOT2_HEADER_MAGIC + MULTIBOOT_ARCHITECTURE_I386 + header_hength)

.global start, _start

.section .text
start:
_start:
jmp multiboot_entry

.align  8

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
multiboot_entry:
movb $'B', 0xb8000
movb $'a', 0xb8002
movb $'o', 0xb8004
movb $'j', 0xb8006
movb $'u', 0xb8008
movb $'a', 0xb800a
movb $'n', 0xb800c
movb $' ', 0xb800e
movb $'m', 0xb8010
movb $'y', 0xb8012
movb $' ', 0xb8014
movb $'v', 0xb8016
movb $'o', 0xb8018
movb $'i', 0xb801a
movb $'c', 0xb801c
movb $'e', 0xb801e
movb $'!', 0xb8020

hlt
