#include <tty/panic.h>

extern void hang(void);

void panic(char *file, unsigned int line, char *str)
{
	tty_printf("Kernel panic - %s @ %d: %s\n", file, line, str);
	hang();
}

