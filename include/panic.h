#ifndef PANIC_H
#define PANIC_H

#include <tty.h>

#define EARLY_PANIC(x) tty_printf("%s @ %d: %s", __FILE__, __LINE__, x) 

#endif
