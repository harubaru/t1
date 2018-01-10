CODE_SEG equ 0x08
DATA_SEG equ 0x10

section .rodata

GDT32:				; 32-bit GDT (obviously)
.null:
	dq 0x0000000000000000	; Null descriptor
.kcode:
	dq 0x00CF9A000000FFFF	; Kernel Code descriptor
.kdata:
	dq 0x00CF92000000FFFF	; Kernel Data descriptor
.ucode:
	dq 0x00CFFA000000FFFF	; User Code descriptor
.udata:
	dq 0x00CFF2000000FFFF	; User Data descriptor
.tss:
	dq 0x00C0F21030000068	; Task State Segment
.ptr:
	dw $ - GDT32 - 1	; Limit
	dd GDT32		; Base

section .text

global gdt_init
gdt_init:
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

global tss_flush
tss_flush:
	mov ax, 0x28
	ltr ax
	ret
