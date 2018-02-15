#ifndef PROCESS_H
#define PROCESS_H

#include <mem/vmm.h>
#include <lib/string.h>

typedef struct process_regs {
	//       0    4    8    12   16   20   24   28   32   36    
	uint32_t eax, ebx, ecx, edx, esi, edi, esp, ebp, eip, eflags;
} process_regs_t;

typedef enum process_state {
	PROCESS_RUNNING = 0,
	PROCESS_RUNABLE = 1,
	PROCESS_SLEEPING = 2,
	PROCESS_ZOMBIE = 3
} process_state_t;

typedef struct process {
	struct process_regs regs;
	struct process *prev, *next;
	page_directory_t *pd;
	process_state_t state;
	uint32_t pid;
	char *name;
} process_t;

process_t *process_init(void (*entry_point)(void), char *name);
void process_force_kill(process_t *proc);
void process_try_kill(process_t *proc);

#endif
