#include <tty/tty.h>
#include <lib/string.h>

extern void hang(void);

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

void common_exception_handler(unsigned int err, unsigned int code)
{
	if (err == 1) {
		tty_printf("A fatal exception had occurred!\nException: %s (0x%s)\n", exception_codes[code], itoa(code, 16));		
		hang();
	} else if (err == 0) {
		tty_printf("A non-fatal exception had occured!\nException: %s (0x%s)\n", exception_codes[code], itoa(code, 16));
	}
}

