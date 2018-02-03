NAME    = kernel
VERSION = 0.00
BINDIR = bin
BINARYNAME = $(NAME)-$(VERSION)
BINARY = $(BINDIR)/$(BINARYNAME)
ISO = $(BINARY).iso

CC = gcc
LD = ld
AS = nasm

CC_OBJS  := $(patsubst %.c, %.o, $(shell find . -name '*.c'))
AS_OBJS := $(patsubst %.asm, %.o, $(shell find . -name '*.asm'))

OBJS = $(AS_OBJS) $(CC_OBJS)

all: $(BINARY)

$(BINARY): $(OBJS)
	@echo "LD $(BINARY)"
	$(LD) -melf_i386 -T memmap -nostdlib -o $(BINARY) $(OBJS)

clean:
	@echo "RM  OBJS"
	rm -rf $(OBJS)
	@echo "RM  $(BINARY)"
	rm -rf $(BINARY)
	rm -rf $(ISO)
	rm -rf ./iso/boot/$(BINARYNAME)
	rm -rf bochsout.txt

grub-iso: $(ISO)

$(ISO): $(BINARY)
	cp $(BINARY) ./iso/boot/kernel
	grub-mkrescue -o $(ISO) ./iso


qemu: $(BINARY)
	@echo "QEMU  $(BINARY)"
	qemu-system-i386 -m 128M -s -kernel $(BINARY)

bochs: $(ISO)
	@echo "BOCHS $(ISO)"
	bochs -f bochsrc.txt
	mv bochsout.txt $(BINDIR)

%.o: %.c
	@echo "CC  $<"
	$(CC) -m32 -Iinclude -Wall -Wextra -O0 -ffreestanding -fno-asynchronous-unwind-tables -c $< -o $@

%.o: %.asm
	@echo "AS  $<"
	$(AS) -felf32 $< -o $@

$(V).SILENT:
