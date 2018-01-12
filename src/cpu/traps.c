#include <tty/tty.h>
#include <tty/panic.h>
#include <lib/string.h>

extern void hang(void);

typedef struct registers
{
	unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
	unsigned int eip, cs, eflags, useresp, ss;
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

void die(unsigned int fatal, unsigned int code, registers_t regs)
{
	if (fatal == 1) {
		tty_printf("==== register dump ====\n");
		tty_printf("EAX=%x EBX=%x ECX=%x EDX=%x\n", regs.eax, regs.ebx, regs.ecx, regs.edx);
		tty_printf("ESI=%x EDI=%x\n", regs.esi, regs.edi);
		tty_printf("ESP=%x EIP=%x EFLAGS=%x\n", regs.esp, regs.eip, regs.eflags);
		tty_printf("=======================\n");
		panic(exception_codes[code]);
	} else if (fatal == 0) {
		tty_printf("%s\n", exception_codes[code]);
	} 
}

