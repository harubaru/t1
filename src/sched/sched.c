#include <sched/sched.h>

extern void context_switch(process_regs_t *regs);

static process_t curr;
static uint32_t last_pid = 0;

void idle(void)
{
	while(1)
		asm volatile ("nop");
}

void sched_irq(void)
{
	pic_ack(0);
	context_switch(&curr.regs);
}

void sched_init(void)
{
	curr = process_init(idle, "idle");
	curr.next = &curr;

	pic_enable_irq(0);
	irq_install_handler(0, (uint32_t)sched_irq);
	pit_set_phase(10);
}

uint32_t sched_last_pid(void)
{
	return last_pid++;
}
