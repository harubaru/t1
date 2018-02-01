#include <sched/sched.h>

extern void context_save(process_regs_t *regs);
extern void context_switch(process_regs_t *regs);

static process_t *curr;
static uint32_t last_pid = 0;
static uint32_t jiffies = 0;

/*
 * The amount of jiffies a process gets
 * before the scheduler switches it to curr->next
 */
#define TIME_SLICE 10

void idle(void)
{
idle_loop:
	asm volatile ("nop");
	goto idle_loop;
}

void sched_irq(void)
{
	asm volatile ("cli");
	asm volatile ("add $12, %esp");

	context_save(&curr->regs);
	pic_ack(0);
	jiffies++;

	if (!(jiffies % TIME_SLICE)) {
		asm volatile ("movl (%%esp), %0" : "=r"(curr->regs.eip));
		jiffies = 0;
		curr = curr->next;
		context_switch(&curr->regs);
	}
	asm volatile ("sti; leave; iret");
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

uint32_t sched_last_pid(void)
{
	return last_pid++;
}
