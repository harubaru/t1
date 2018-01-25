#include <cpu/pit.h>

#define PIT_0 0x40 // channel 0
#define PIT_COMMAND 0x43

uint32_t pit_jiffies;

void pit_irq(void)
{
	pit_jiffies++;
	return;
}

void pit_init(void)
{
	pic_enable_irq(0);
	irq_install_handler(0, (uint32_t)pit_irq);
	pit_set_phase(1000);
}

void pit_set_phase(uint32_t hz)
{
	uint32_t divisor = PIT_HZ / hz;

	outb(PIT_COMMAND, 0x36);
	outb(PIT_0, divisor & 0xFF);
	outb(PIT_0, (divisor >> 8) & 0xFF);
}

void pit_sleep(uint32_t ms)
{
	uint32_t now = pit_jiffies;

	while ((pit_jiffies - now) < ms);
}