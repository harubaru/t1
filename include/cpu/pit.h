#ifndef PIT_H
#define PIT_H

#include <cpu/pic.h>
#include <cpu/irq.h>

#define PIT_HZ 1193181

extern uint32_t pit_jiffies;

void pit_init(void);
void pit_set_phase(uint32_t hz);
void pit_sleep(uint32_t ms);

#endif
