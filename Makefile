NAME    = kernel
VERSION = 0.00
BINARY = $(NAME)-$(VERSION)
ISO = $(BINARY).iso

CC = gcc
LD = ld
AS = nasm

CC_OBJS  := $(patsubst %.c, %.o, $(shell find . -name '*.c'))
AS_OBJS := $(patsubst %.asm, %.o, $(shell find . -name '*.asm'))

OBJS = $(AS_OBJS) $(CC_OBJS)

all: $(OBJS)
	@echo "LD $(BINARY)"
	$(LD) -melf_i386 -T memmap -nostdlib -o $(BINARY) $(OBJS)

clean:
	@echo "RM  OBJS"
	rm -rf $(OBJS)
	@echo "RM  $(BINARY)"
	rm -rf $(BINARY)
	rm -rf ./iso/boot/kernel
	rm -rf *.iso
	rm -rf bochsout.txt

grub-iso:
	cp $(BINARY) ./iso/boot/kernel
	grub-mkrescue -o $(BINARY).iso ./iso 

qemu:
	@echo "QEMU  $(BINARY)"
	qemu-system-i386 -m 128M -s -kernel $(BINARY)

bochs:
	@echo "BOCHS $(ISO)"
	bochs -f bochsrc.txt

%.o: %.c
	@echo "CC  $<"
	$(CC) -m32 -Iinclude -Wall -Wextra -O0 -ffreestanding -fno-asynchronous-unwind-tables -c $< -o $@

%.o: %.asm
	@echo "AS  $<"
	$(AS) -felf32 $< -o $@

$(V).SILENT:
