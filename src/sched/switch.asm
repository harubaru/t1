
; void sched_jump(unsigned long eip);
global sched_jump
sched_jump:
	mov eax, [esp + 4]
	jmp eax
 