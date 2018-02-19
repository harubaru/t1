#ifndef SCHED_H
#define SCHED_H

#include <cpu/idt.h>
#include <cpu/pic.h>
#include <cpu/pit.h>
#include <tty/panic.h>
#include <sched/process.h>

void sched_init(process_t *proc);
void sched_add(process_t *proc);
void sched_remove(process_t *proc);
unsigned long sched_pid_alloc(void);
unsigned long sched_step(void);

#endif
