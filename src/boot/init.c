#include <boot/multiboot.h>
#include <cpu/idt.h>
#include <cpu/tss.h>
#include <cpu/pic.h>
#include <cpu/pit.h>
#include <cpu/irq.h>
#include <drivers/ps2/ps2kbd.h>
#include <tty/tty.h>
#include <mem/vmm.h>
#include <sched/process.h>

extern void __gdt_init(void);

#define OK tty_puts(" SUCCESS!\n", tty_default_bg(), TTY_LIGHT_GREEN);
#define FAILED tty_puts(" FAILED!\n", tty_default_bg(), TTY_LIGHT_RED);

void init_arch(struct multiboot_info *mb)
{
	tty_printf("Initializing arch specific code... ");

	__gdt_init();
	vmm_init((void *)(mb->mem_upper + 2048));
	tss_init();
	idt_init();
	pic_init();
	irq_init();

	OK
}

void init(struct multiboot_info *mb)
{
	tty_init(TTY_WHITE, TTY_BLACK);
	tty_printf("Kernel version %s\n", __KVERSION__);
	init_arch(mb);

	return;
}
