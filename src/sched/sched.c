#include <sched/sched.h>

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
