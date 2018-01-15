[bits 32]

; Multiboot Header
MB_ALIGN    equ 1<<0
MB_MEMINFO  equ 1<<1
MB_FLAGS    equ MB_ALIGN | MB_MEMINFO
MB_MAGIC    equ 0x1BADB002
MB_CHECKSUM equ -(MB_MAGIC + MB_FLAGS)

section .multiboot
align 4
	dd MB_MAGIC
	dd MB_FLAGS
	dd MB_CHECKSUM

section .text

global _start
_start:
	mov esp, stack_top
	
	push ebx ; pointer to multiboot info struct

	extern init
	call init

	jmp hang


global hang
hang:	cli
	hlt
	jmp hang


section .bss
align 16
stack_bottom:
resb 0x4000
stack_top:
