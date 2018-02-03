#ifndef SCHED_H
#define SCHED_H

#include <cpu/irq.h>
#include <cpu/idt.h>
#include <cpu/pit.h>
#include <sched/process.h>

void sched_init(void);
void sched_add_process(process_t *proc);
void sched_remove_process(process_t *proc);
uint32_t sched_last_pid(void);

#endif
