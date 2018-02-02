#include <tty/tty.h>
#include <tty/panic.h>
#include <lib/string.h>

extern void hang(void);

typedef struct registers
{
	unsigned int eip, eflags, edi, esi, ebp, esp, ebx, edx, ecx, eax;
} registers_t;

char *exception_codes[] = 
{
	"Division by zero",
	"Debug",
	"Non-Maskable Interrupt",
	"Breakpoint",
	"Overflow",
	"Bound Range Exceeded",
	"Invalid Opcode",
	"Device Not Available",
	"Double Fault",
	"Coprocessor Segment Overrun",
	"Invalid TSS",
	"Segment Not Present",
	"Stack-Segment Fault",
	"General Protection Fault",
	"Page Fault",
	"reserved",
	"x87 Floating-Point Exception",
	"Alignment Check",
	"Machine Check",
	"SIMD Floating-Point Exception",
	"Virtualization Exception",
	"reserved",
	"reserved",
	"reserved",
	"reserved",
	"reserved",
	"reserved",
	"reserved",
	"reserved",
	"Security Exception",
	"reserved"
};

void trap_fatal(unsigned int code, registers_t regs)
{
	tty_printf("\n==== register dump ====\n");
	tty_printf("EAX=%x EBX=%x ECX=%x EDX=%x\n", regs.eax, regs.ebx, regs.ecx, regs.edx);
	tty_printf("ESI=%x EDI=%x\n", regs.esi, regs.edi);
	tty_printf("ESP=%x EIP=%x EFLAGS=%x\n", regs.esp, regs.eip, regs.eflags);
	tty_printf("=======================\n");
	panic(exception_codes[code]);
}

void trap_warn(unsigned int code)
{
	tty_printf("%s\n", exception_codes[code]);
}
