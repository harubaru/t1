
extern irq
extern hang

; arg 1: irq number, arg 2: int number
%macro IRQ 2
	global irq_%1
irq_%1:
	mov edx, %1
	jmp irq_stub
%endmacro

IRQ 0, 32
IRQ 1, 33
IRQ 2, 34
IRQ 3, 35
IRQ 4, 36
IRQ 5, 37
IRQ 6, 38
IRQ 7, 39
IRQ 8, 40
IRQ 9, 41
IRQ 10, 42
IRQ 11, 43
IRQ 12, 44
IRQ 13, 45
IRQ 14, 46
IRQ 15, 47

irq_stub:
	pusha

	push edx
	call irq
	add esp, 4
	
	popa
	iret