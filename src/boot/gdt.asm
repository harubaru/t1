CODE_SEG equ 0x08
DATA_SEG equ 0x10

section .data

GDT32:				; 32-bit GDT (obviously)
	dq 0x0000000000000000	; Null descriptor
	dq 0x00CF9A000000FFFF	; Kernel Code descriptor
	dq 0x00CF92000000FFFF	; Kernel Data descriptor
	dq 0x00CFFA000000FFFF	; User Code descriptor
	dq 0x00CFF2000000FFFF	; User Data descriptor

global GDT32_tss
GDT32_tss:
	dq 0x0000000000000000

GDT32.ptr:
	dw $ - GDT32 - 1
	dd GDT32

section .text

global __gdt_init
__gdt_init:
	lgdt [GDT32.ptr]
	jmp CODE_SEG:.flush

.flush: ; flush data segment registers
	mov ax, DATA_SEG ; point to new data segment
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

	ret

global __tss_flush
__tss_flush:
	mov ax, 0x28
	ltr ax

	ret
