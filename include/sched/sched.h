#ifndef SCHED_H
#define SCHED_H

#include <cpu/irq.h>
#include <cpu/pit.h>
#include <sched/process.h>

void sched_init(void);
uint32_t sched_last_pid(void);

#endif
