#include <sched/sched.h>

extern void sched_jump(unsigned long eip);

static process_t *curr = NULL;
static unsigned long pid = 0;

void sched_init(process_t *proc)
{
	if (proc) {
		curr = proc;

		curr->prev = curr;
		curr->next = curr;
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

void sched_step(void)
{
	if (curr && curr->next) {
		switch (curr->state) {
		case PROCESS_RUNNING:
			PANIC("trying to schedule a running process!");
			break;
		case PROCESS_RUNABLE:
			curr->state = PROCESS_RUNNING;
			sched_jump(curr->regs.eip);
			curr->state = PROCESS_RUNABLE;
			break;
		case PROCESS_SLEEPING:
			// do nothing and let it sleep
			break;
		case PROCESS_ZOMBIE:
			curr = curr->next;
			sched_remove(curr->prev);
			return;
		default:
			PANIC("cannot handle unknown process state!");
		}
		curr = curr->next;
	} else {
		PANIC("no more processes to schedule!");
	}
}
