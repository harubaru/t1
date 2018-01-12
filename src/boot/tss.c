#include <boot/tss.h>

#include <tty/tty.h>
#include <lib/string.h>

#define IOPL_3 (0x00003000)

struct tss kernel_tss;
extern uint64_t GDT32_tss;

static uint64_t create_desc(uint32_t base, uint32_t limit, uint16_t flag)
{
	uint64_t desc = 0;

	desc = limit & 0x000F0000;
	desc |= (flag << 8) & 0x00F0FF00;
	desc |= (base >> 16) & 0x000000FF;
	desc |= base & 0xFF00000;

	desc <<= 32;

	desc |= base << 16;
	desc |= limit & 0x0000FFFF;

	return desc;
}

void tss_init(void)
{
	uint64_t tss_desc = create_desc((uint32_t)&kernel_tss, sizeof(struct tss), 0xE9);

	GDT32_tss |= tss_desc;

	memset(&kernel_tss, 0, sizeof(tss_t));

	kernel_tss.ss0 = 0x10;
	kernel_tss.ss1 = 0;
	kernel_tss.ss2 = 0;
	kernel_tss.esp0 = 0;
	kernel_tss.eflags = 2 | IOPL_3;

	kernel_tss.iomap = sizeof(struct tss);

	__tss_flush();
}

struct tss *tss_get(void)
{
	return &kernel_tss;
}
