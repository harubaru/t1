#include <tty/tty.h>
#include <drivers/ps2/ps2kbd.h>

static int curr_scancode;

void ps2kbd_irq(void)
{
	uint8_t status = inb(0x64);
	uint8_t scancode;

	if (status & 1) {
		scancode = inb(0x60);
		if (scancode > 128)
			curr_scancode = scancode - 128; // todo: handle caps lock and shift
	}
}

int ps2kbd_get_scancode(void)
{
	return curr_scancode;
}

void ps2kbd_init(void)
{
	irq_install_handler(1, (uint32_t)ps2kbd_irq);
	pic_enable_irq(1);
}
