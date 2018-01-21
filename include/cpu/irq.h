#ifndef IRQ_H
#define IRQ_H

#include <cpu/pic.h>

void irq_init(void);
void irq_install_handler(uint32_t i, uint32_t offset);

#endif
