#include <sched/sched.h>

extern void context_switch(process_regs_t *regs);

static process_t *curr;
static uint32_t last_pid = 0;
static uint32_t jiffies = 0;

void idle(void)
{
	for (;;)
		asm volatile ("hlt");
}

void sched_irq(void)
{
	jiffies++;
	pic_ack(0);
	if (!(jiffies % 10)) {
		jiffies = 0;
		tty_printf("%d ", jiffies);
		context_switch(&curr->next->regs);
	}
	asm volatile ("leave; iret");
}

void sched_init(void)
{
	curr = process_init(idle, "idle");
	curr->next = curr;

	idt_set_entry(32, (uint32_t)sched_irq);
	pic_enable_irq(0);
	pit_set_phase(1000);
}

uint32_t sched_last_pid(void)
{
	return last_pid++;
}
