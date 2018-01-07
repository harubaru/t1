#include <tty.h>
#include <boot/multiboot.h>
#include <lib/string.h>
#include <interrupt/pic.h>
#include <mem/vmm.h>

extern void gdt_init(void);
extern void idt_init(void);

void kernel_init(struct multiboot_info *mb, unsigned int mb_magic)
{
	asm volatile ("cli"); /* disable interrupts during setup */

	gdt_init();
	idt_init();
	pic_init();

	tty_init(TTY_WHITE, TTY_BLACK);

	asm volatile ("sti"); /* reenable them afterwards */

	if (mb_magic != MULTIBOOT_MAGIC) {
		tty_printf("Kernel not booted by compliant bootloader\n");
		return;
	}

	vmm_init((void *)0x1000000);

	return;
}
