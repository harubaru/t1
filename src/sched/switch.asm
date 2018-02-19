
; void sched_jump(unsigned long eip);
global sched_jump
sched_jump:
	pop eax
	
	pushfd
	or dword [esp], 0x200
	push 0x8
	push eax

	iret
 