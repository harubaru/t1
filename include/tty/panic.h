#ifndef PANIC_H
#define PANIC_H

#include <tty/tty.h>

#define PANIC(x) panic_dbg(__FILE__, __LINE__, x);

void panic(char *str);
void panic_dbg(char *file, unsigned int line, char *str);

#endif
