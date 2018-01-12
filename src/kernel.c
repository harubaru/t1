#include <tty/tty.h>
#include <boot/idt.h>
#include <boot/multiboot.h>
#include <boot/tss.h>
#include <lib/string.h>
#include <cpu/pic.h>
#include <mem/vmm.h>

extern void __gdt_init(void);

void kernel_init(struct multiboot_info *mb)
{
	__gdt_init();
	tss_init();
	idt_init();
	pic_init();
	vmm_init((void *)(mb->mem_upper + 2048));

	return;
}
