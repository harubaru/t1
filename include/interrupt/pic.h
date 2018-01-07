#ifndef PIC_H
#define PIC_H

#include <io.h>

void pic_init(void);
void pic_ack(uint8_t irq);

#endif
