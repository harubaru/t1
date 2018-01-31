#include <sched/process.h>

process_regs_t curr_regs;

process_t *process_init(void (*entry_point)(void), char *name)
{
	process_t *proc = vmm_malloc(sizeof(process_t));
	memset(proc, 0, sizeof(process_t));

	proc->pd = vmm_init_pd();
	vmm_copy_pd(proc->pd, kern_pd);

	// get eflags
	asm volatile("pushfl; \
		 movl (%%esp), %%eax; \
		 movl %%eax, %0; popfl;" : 
		 "=rm"(proc->regs.eflags));

	proc->regs.esp = (uint32_t)vmm_malloc(0x1000);
	proc->regs.ebp = proc->regs.esp + 0x1000;
	proc->regs.eip = (uint32_t)entry_point;
	proc->regs.cr3 = (uint32_t)proc->pd->pd;
	proc->pid = sched_last_pid();
	proc->name = name;

	return proc;
}

void process_kill(process_t *proc)
{
	vmm_free_pd(proc->pd);
	vmm_free((uint32_t *)proc->regs.esp);
}
