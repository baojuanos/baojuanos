CC=clang
CFLAGS=-Wall -ffreestanding -g -Iinclude
LINK_SCRIPT=scripts/kernel.ld
MKISO_SCRIPT=scripts/mkiso.sh

TARGET_DIR=target
KERNEL=$(TARGET_DIR)/kernel
ISO_DIR=$(TARGET_DIR)/iso
ISO=$(TARGET_DIR)/baojuanos.iso

asm_src=$(shell find arch -name *.S)
asm_objs=$(patsubst %.S, %.o, $(asm_src))

objects=$(asm_objs)

kernel: $(objects)
	ld -T $(LINK_SCRIPT) $(objects) -o $(KERNEL)
	objdump -SD -Msuffix $(KERNEL) > $(KERNEL).asm

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: check_multiboot iso run clean

iso: kernel
	sh $(MKISO_SCRIPT) $(KERNEL) $(ISO)

check_multiboot:
	grub-file --is-x86-multiboot2 $(KERNEL)

run: iso
	qemu-system-x86_64 -boot d -cdrom $(ISO)

clean:
	rm -rf target/* $(objects)
