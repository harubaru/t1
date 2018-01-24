#include <drivers/ps2/ps2kbd.h>

static char ps2kbd_lower_set[] = {
	0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
	'\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
	0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
	0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
	0, 0, ' ' // Rest of everything can just be ignored when we process the keys.
};

static char ps2kbd_higher_set[] = {
	0, 0, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b',
	'\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',
	0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '\"', '~',
	0, '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0,
	0, 0, ' ' // Rest of everything can just be ignored when we process the keys.
};

static int shift_pressed = 0;
static int event = 0;

static int curr_scancode;
static char curr_char;

static char scancode_to_ascii(int scancode)
{
	if (scancode >= 128)
		return 0;
	
	if (shift_pressed)
		return ps2kbd_higher_set[scancode];

	return ps2kbd_lower_set[scancode];
}

void ps2kbd_irq(void)
{
	uint8_t status = inb(0x64);

	if (status & 1) {
		event = 1;
		curr_scancode = inb(0x60);

		if (curr_scancode < 128) { // pressed
			if ((curr_scancode == PS2KBD_LSHIFT) || (curr_scancode == PS2KBD_RSHIFT))
				shift_pressed = 1;
		} else {		   // released
			if ((curr_scancode == PS2KBD_LSHIFT + PS2KBD_RELEASED) || curr_scancode == (PS2KBD_RSHIFT + PS2KBD_RELEASED))
				shift_pressed = 0;
		}

		curr_char = scancode_to_ascii(curr_scancode);
	}
}

int ps2kbd_get_scancode(void)
{
	while (event != 1);
	event = 0;
	
	return curr_scancode;
}

char ps2kbd_get_char(void)
{
	while (event != 1);
	event = 0;
	
	return curr_char;
}

void ps2kbd_init(void)
{
	irq_install_handler(1, (uint32_t)ps2kbd_irq);
	pic_enable_irq(1);
}
