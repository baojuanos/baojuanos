CC=clang
LD=ld.lld
CFLAGS=-Wall -m64 -g -ffreestanding -fno-builtin -nostdinc -Iinclude -I.
LINK_SCRIPT=scripts/kernel.ld
MKISO_SCRIPT=scripts/mkiso.sh

TARGET_DIR=target
KERNEL=$(TARGET_DIR)/kernel
ISO_DIR=$(TARGET_DIR)/iso
ISO=$(TARGET_DIR)/baojuanos.iso

asm_src=$(shell find arch -name *.S)
asm_obj=$(patsubst %.S, %.o, $(asm_src))
c_src=$(shell find arch kernel -name *.c)
c_obj=$(patsubst %.c, %.o, $(c_src))

objects=$(asm_obj) $(c_obj)

kernel: $(objects)
	$(LD) -T $(LINK_SCRIPT) $(objects) -o $(KERNEL) -M > $(KERNEL).map
	objdump -SD -Msuffix $(KERNEL) > $(KERNEL).asm

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: iso run clean

iso: kernel
	sh $(MKISO_SCRIPT) $(KERNEL) $(ISO)

run: iso
	DISPLAY=:0 qemu-system-x86_64 -boot d -cdrom $(ISO) -monitor stdio

clean:
	rm -rf target/* $(objects)
