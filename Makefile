NAME    = kernel
VERSION = 0.00
BINARY = $(NAME)-$(VERSION)

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

run:
	@echo "QEMU  $(BINARY)"
	qemu-system-i386 -s -kernel $(BINARY)

%.o: %.c
	@echo "CC  $<"
	$(CC) -m32 -Iinclude -Wall -Wextra -O0 -ffreestanding -fno-asynchronous-unwind-tables -c $< -o $@

%.o: %.asm
	@echo "AS  $<"
	$(AS) -felf32 $< -o $@

$(V).SILENT:
