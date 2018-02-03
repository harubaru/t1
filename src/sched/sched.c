#include <sched/sched.h>

extern void context_save(process_regs_t *regs);
extern void context_switch(process_regs_t *regs);
extern void context_iret(uint32_t ret);

static process_t *curr;
static uint32_t last_pid = 0;
static uint32_t jiffies = 0;

/*
 * The amount of jiffies a process gets
 * before the scheduler switches it to curr->next
 */
#define TIME_SLICE 100

void idle(void)
{
idle_loop:
	asm volatile ("hlt");
	goto idle_loop;
}

void sched_irq(void)
{
	asm volatile ("cli");

	context_save(&curr->regs);
	pic_ack(0);
	jiffies++;

	asm volatile ("movl 12(%%esp), %0" : "=r"(curr->regs.eip));

	if (jiffies == TIME_SLICE) {
		jiffies = 0;
		curr = curr->next;
		asm ("addl $0x38, %esp");
		context_switch(&curr->regs);
	}
	asm ("leave; iret");
}

void sched_init(void)
{
	curr = process_init(idle, "idle");
	curr->next = curr;

	idt_set_entry(32, (uint32_t)sched_irq);
	pic_enable_irq(0); 
	pit_set_phase(PIT_HZ / 1000);

	idle();
}

void sched_add_process(process_t *proc)
{
	proc->next = curr->next;
	curr->next = proc;
}

void sched_remove_process(process_t *proc)
{
	process_t *i = curr;

	while (1) {
		if ((i->next == proc) || (i == proc)) {
			i->next = proc->next;
			break;
		} else {
			i = i->next;
		}
	}
}

uint32_t sched_last_pid(void)
{
	return last_pid++;
}
