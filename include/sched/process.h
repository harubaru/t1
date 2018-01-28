#ifndef PROCESS_H
#define PROCESS_H

#include <tty/tty.h>
#include <mem/vmm.h>
#include <lib/string.h>

typedef struct process_regs {
	uint32_t eax, ebx, ecx, edx, esi, edi, esp, ebp, eip, eflags, cr3;
} process_regs_t;

typedef struct process {
	struct process_regs regs;
	struct process *next;
	page_directory_t *pd;
	char *name;
} process_t;

process_t process_init(void (*entry_point)(void), char *name);
void process_kill(process_t proc);

#endif
