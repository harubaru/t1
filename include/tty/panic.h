#ifndef PANIC_H
#define PANIC_H

#include <tty/tty.h>

#define PANIC(x) panic(__FILE__, __LINE__, x);

void panic(char *file, unsigned int line, char *str);

#endif
