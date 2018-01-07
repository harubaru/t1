
extern common_exception_handler

%macro ERR 1
	global exception_%1
exception_%1:
	cli
	pusha

	push dword %1
	push dword 1
	call common_exception_handler

	add esp, 8 ; balance out stack

	popa
	sti
	iret
%endmacro

%macro NOERR 1
	global exception_%1
exception_%1:
	cli
	pusha

	push dword %1
	push dword 0
	call common_exception_handler

	add esp, 8

	popa
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

