#ifndef PIC_H
#define PIC_H

#include <cpu/io.h>

void pic_init(void);
void pic_enable_irq(uint8_t irq);
void pic_disable_irq(uint8_t irq);
void pic_ack(uint8_t irq);

#endif
