#include <tty/tty.h>

#include <lib/string.h>
#include <stdarg.h>
#include <stdint.h>

static uint16_t *vbuf;
static uint16_t x;
static uint16_t y;

static enum tty_color default_bg;
static enum tty_color default_fg;

static uint16_t entry(char c, enum tty_color fg, enum tty_color bg) {
	uint8_t uc = (uint8_t)c;
	uint8_t color = fg | bg << 4;
	return (uint16_t) uc | (uint16_t) color << 8;
}

static void scroll(void)
{
	uint16_t empty = entry(' ', default_fg, default_bg);
	uint32_t i;

	// scroll up
	for (i = 0; i < (TTY_HEIGHT - 1) * TTY_WIDTH; i++)
		*(vbuf + i) = *(vbuf + (i + 80));

	// make new line empty
	for (i = (TTY_HEIGHT - 1) * TTY_WIDTH; i == TTY_HEIGHT * TTY_WIDTH; i++)
		*(vbuf + i) = empty;
}

void tty_init(enum tty_color fg, enum tty_color bg)
{
	uint32_t index;
	uint32_t tx;
	uint32_t ty;
	vbuf = (uint16_t *)0xB8000;
	x = 0;
	y = 0;
	default_fg = fg;
	default_bg = bg;
	for (ty = 0; ty < TTY_HEIGHT; ty++) {
		for (tx = 0; tx < TTY_WIDTH; tx++) {
			index = ty * TTY_WIDTH + tx;
			*(vbuf + index) = entry(' ', bg, bg); 
		}
	}
}

void tty_putc(char c, enum tty_color fg, enum tty_color bg)
{
	uint32_t index = y * TTY_WIDTH + x;

	if(c == '\n') {
		y++;
		x = 0;
		return;
	}

	*(vbuf + index) = entry(c, fg, bg);

	if (++x == TTY_WIDTH) {
		x = -1;
	}

	if (y == TTY_HEIGHT) {
		y--;
		scroll();
	}
}

void tty_puts(char *c, enum tty_color fg, enum tty_color bg)
{
	while (*c != 0)
		tty_putc(*c++, fg, bg);
}

void tty_printf(char *str, ...)
{
	if(!str)
		return;

	va_list ap;
	va_start(ap, str);

	char *tmp = 0;
	uint32_t i = 0;
	while (str[i] != 0) {
		if ((str[i] == '%')) {
			switch(str[i + 1]) {
				/* string */
				case 's':
					tmp = va_arg(ap, char*);
					tty_puts(tmp, default_fg, default_bg);
					i += 2;
					continue;
				/* decimal */
				case 'd': {
					int c = va_arg(ap, int);
					if (!c)
						tty_putc('0', default_fg, default_bg);
					tmp = itoa(c, 10);
					tty_puts(tmp, default_fg, default_bg);
					i += 2;
					continue;
				}
				/* hex */
				case 'x': {
					int c = va_arg(ap, int);
					if (!c)
						tty_puts("(null)", default_fg, default_bg);
					
					tmp = itoa(c, 16);
					tty_puts(tmp, default_fg, default_bg);
					i += 2;
					continue;
				}
				/* pointers */
				case 'p': {
					void *p = va_arg(ap, void *);
					if (!p)
						tty_puts("(null)", default_fg, default_bg);

					tmp = itoa((uint32_t)p, 16);
					tty_puts(tmp, default_fg, default_bg);
					i += 2;
					continue;
				}
				default:
					  break;
			}
		} else {
			tty_putc(str[i++], default_fg, default_bg);
		}
	}
	va_end(ap);
}

