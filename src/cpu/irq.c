#include <cpu/irq.h>

#include <tty/tty.h>

uint32_t irq_handlers[256];

void irq_init(void)
{
	asm volatile ("sti");

	uint32_t i;
	for (i = 0; i < 256; i++)
		irq_handlers[i] = 0;
}

void irq_install_handler(uint32_t i, uint32_t offset)
{
	if (i < 256)
		irq_handlers[i] = offset;
}

void irq(uint32_t i)
{
	pic_ack(i);

	void (*handler)(void) = (void *)irq_handlers[i];
	if (handler != 0)
		handler();
	else
		tty_printf("Unhandled IRQ: %d\n", i);
}
