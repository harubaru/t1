#include <cpu/irq.h>

#include <tty/tty.h>

uint32_t irq_handlers[256];

void irq_install_handler(uint32_t i, uint32_t offset)
{
	if (i < 256)
		irq_handlers[i] = offset;
}

void irq(uint32_t i)
{
	tty_printf("%d\n", i);
	void (*handler)(void) = (void *)irq_handlers[i];
	if (handler != 0)
		handler();

	pic_ack(i);
}
