global context_save
context_save:
	pusha ; 32

	mov eax, [esp + 36]
	mov [eax + 4], ebx
	mov [eax + 8], ecx
	mov [eax + 12], edx
	mov [eax + 16], esi
	mov [eax + 20], edi

	popa
	ret

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

	push 0x206 ; eflags
	push 0x08 ; cs

	mov eax, [ebp + 32]
	push eax ; eip

	mov eax, [ebp + 0]
	mov ebp, [ebp + 28]

	iret
