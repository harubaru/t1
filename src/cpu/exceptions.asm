
extern trap_fatal
extern trap_warn

%macro ERR 1
	global exception_%1
exception_%1:
	cli
	pusha
	pushfd
	mov eax, [esp + 36]
	push eax

	push dword %1
	call trap_fatal
%endmacro

%macro NOERR 1
	global exception_%1
exception_%1:
	cli
	pusha

	mov ax, ds
	push eax

	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax


	push dword %1
	call trap_warn

	pop ebx
	mov ds, bx
	mov es, bx
	mov fs, bx
	mov gs, bx

	popa
	add esp, 0x4
	sti
	iret
%endmacro

NOERR 0  ; divide by zero
NOERR 1  ; debug
NOERR 2  ; nmi
NOERR 3  ; breakpoint
NOERR 4  ; overflow
NOERR 5  ; bound range exceeded
NOERR 6  ; invalid opcode
NOERR 7  ; device not available
ERR 8	 ; double fault
NOERR 9  ; coprocessor segment overrun
ERR 10 	 ; invalid tss
ERR 11	 ; segment not present
ERR 12	 ; stack-segment fault
ERR 13	 ; general protection fault
ERR 14	 ; page fault
NOERR 15 ; reserved
NOERR 16 ; x87 floating-point exception
ERR 17	 ; alignment check
NOERR 18 ; machine check
NOERR 19 ; simd floating-point exception
NOERR 20 ; virtualization exception
NOERR 21 ; reserved
NOERR 22 ; reserved
NOERR 23 ; reserved
NOERR 24 ; reserved
NOERR 25 ; reserved
NOERR 26 ; reserved
NOERR 27 ; reserved
NOERR 28 ; reserved
NOERR 29 ; reserved
ERR 30	 ; security exception
NOERR 31 ; reserved

