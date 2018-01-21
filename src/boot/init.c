#include <boot/multiboot.h>
#include <cpu/idt.h>
#include <cpu/tss.h>
#include <cpu/pic.h>
#include <cpu/irq.h>
#include <tty/tty.h>
#include <mem/vmm.h>

extern void __gdt_init(void);

void init(struct multiboot_info *mb)
{
	tty_init(TTY_WHITE, TTY_BLACK);
	vmm_init((void *)(mb->mem_upper + 2048));
	__gdt_init();
	tss_init();
	idt_init();
	pic_init();
	irq_init();

	for(;;);

	return;
}
