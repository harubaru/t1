#ifndef TTY_H
#define TTY_H

#define TTY_WIDTH  80
#define TTY_HEIGHT 25

enum tty_color {
	TTY_BLACK = 0,
	TTY_BLUE = 1,
	TTY_GREEN = 2,
	TTY_CYAN = 3,
	TTY_RED = 4,
	TTY_MAGENTA = 5,
	TTY_BROWN = 6,
	TTY_LIGHT_GREY = 7,
	TTY_GREY = 8,
	TTY_LIGHT_BLUE = 9,
	TTY_LIGHT_GREEN = 10,
	TTY_LIGHT_CYAN = 11,
	TTY_LIGHT_RED = 12,
	TTY_LIGHT_MAGENTA = 13,
	TTY_LIGHT_BROWN = 14,
	TTY_WHITE = 15
};

void tty_init(enum tty_color fg, enum tty_color bg);
void tty_putc(char c, enum tty_color fg, enum tty_color bg);
void tty_puts(char *c, enum tty_color fg, enum tty_color bg);
void tty_printf(char *str, ...);
enum tty_color tty_default_fg(void);
enum tty_color tty_default_bg(void);

#endif

