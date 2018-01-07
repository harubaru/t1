#include <tty.h>
#include <boot/idt.h>
#include <boot/multiboot.h>
#include <lib/string.h>
#include <interrupt/pic.h>
#include <mem/vmm.h>

extern void gdt_init(void);

void kernel_init()
{
	gdt_init();
	idt_init();
	pic_init();
	vmm_init((void *)0x1000000);

	return;
}
