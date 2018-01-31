global context_switch
context_switch:
	mov ebp, [esp + 4]
	mov ebx, [ebp + 4]
	mov ecx, [ebp + 8]
	mov edx, [ebp + 12]
	mov esi, [ebp + 16]
	mov edi, [ebp + 20]

	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	sti
	pushfd ; eflags
	push 0x08 ; cs

	mov eax, [ebp + 32]
	push eax ; eip

	mov eax, [ebp + 0]
	mov ebp, [ebp + 28]

	iret
