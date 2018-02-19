#include <sched/sched.h>

extern void sched_jump(unsigned long eip);

static process_t *curr = NULL;
static unsigned long pid = 0;

void sched_int(void)
{
	asm ("cli");

	asm ("out %%al, %%dx" : : "d"(0x20), "a"(0x20));

	// save registers
	asm ("mov %%ebx, %0" : "=r"(curr->regs.ebx));
	asm ("mov %%ecx, %0" : "=r"(curr->regs.ecx));
	asm ("mov %%edx, %0" : "=r"(curr->regs.edx));

	asm ("mov %%esi, %0" : "=r"(curr->regs.esi));
	asm ("mov %%edi, %0" : "=r"(curr->regs.edi));

	asm ("mov %%esp, %0" : "=r"(curr->regs.esp));
	asm ("mov %%ebp, %0" : "=r"(curr->regs.ebp));
	
	asm ("mov 12(%%esp), %0" : "=r"(curr->regs.eip));

	if (sched_step() == 1) {

		// restore registers

		asm ("mov %0, %%ebx" : "=r"(curr->regs.ebx));
		asm ("mov %0, %%ecx" : "=r"(curr->regs.ecx));
		asm ("mov %0, %%edx" : "=r"(curr->regs.edx));

		asm ("mov %0, %%esi" : "=r"(curr->regs.esi));
		asm ("mov %0, %%edi" : "=r"(curr->regs.edi));

	//	asm ("mov %0, %%esp" : "=r"(curr->regs.esp));
	//	asm ("mov %0, %%ebp" : "=r"(curr->regs.ebp));

		sched_jump(curr->regs.eip);
	}

	asm ("sti; leave; iret");
}

void sched_init(process_t *proc)
{
	if (proc) {
		curr = proc;

		curr->prev = curr;
		curr->next = curr;
	
		idt_set_entry(32, (unsigned long)sched_int);
		pit_set_phase(PIT_HZ / 1000);
		pic_enable_irq(0);
	}
}

void sched_add(process_t *proc)
{
	if (proc) {
		proc->next = curr->next;
		proc->next->prev = proc;
		proc->prev = curr;
		curr->next = proc;
	}
}

void sched_remove(process_t *proc)
{
	if (proc) {
		proc->prev->next = proc->next;
		proc->next->prev = proc->prev;
	}
}

unsigned long sched_pid_alloc(void)
{
	return pid++;
}

unsigned long sched_step(void)
{
	unsigned long schedule = 0;

	if (curr && curr->next) {
		switch (curr->state) {
		case PROCESS_RUNABLE:
			schedule = 1;
			break;
		case PROCESS_SLEEPING:
			// do nothing and let it sleep
			break;
		case PROCESS_ZOMBIE:
			curr = curr->next;
			sched_remove(curr->prev);
			return 0;
		default:
			PANIC("cannot handle unknown process state!");
		}
		curr = curr->next;
	} else {
		PANIC("no more processes to schedule!");
	}

	return schedule;
}
