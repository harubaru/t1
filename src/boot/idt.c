#include <boot/idt.h>
#include <lib/string.h>

extern void exception_0();
extern void exception_1();
extern void exception_2();
extern void exception_3();
extern void exception_4();
extern void exception_5();
extern void exception_6();
extern void exception_7();
extern void exception_8();
extern void exception_9();
extern void exception_10();
extern void exception_11();
extern void exception_12();
extern void exception_13();
extern void exception_14();
extern void exception_15();
extern void exception_16();
extern void exception_17();
extern void exception_18();
extern void exception_19();
extern void exception_20();
extern void exception_21();
extern void exception_22();
extern void exception_23();
extern void exception_24();
extern void exception_25();
extern void exception_26();
extern void exception_27();
extern void exception_28();
extern void exception_29();
extern void exception_30();
extern void exception_31();

static uint32_t vectors[32] = {
	(uint32_t) exception_0,
	(uint32_t) exception_1,
	(uint32_t) exception_2,
	(uint32_t) exception_3,
	(uint32_t) exception_4,
	(uint32_t) exception_5,
	(uint32_t) exception_6,
	(uint32_t) exception_7,
	(uint32_t) exception_8,
	(uint32_t) exception_9,
	(uint32_t) exception_10,
	(uint32_t) exception_11,
	(uint32_t) exception_12,
	(uint32_t) exception_13,
	(uint32_t) exception_14,
	(uint32_t) exception_15,
	(uint32_t) exception_16,
	(uint32_t) exception_17,
	(uint32_t) exception_18,
	(uint32_t) exception_19,
	(uint32_t) exception_20,
	(uint32_t) exception_21,
	(uint32_t) exception_22,
	(uint32_t) exception_23,
	(uint32_t) exception_24,
	(uint32_t) exception_25,
	(uint32_t) exception_26,
	(uint32_t) exception_27,
	(uint32_t) exception_28,
	(uint32_t) exception_29,
	(uint32_t) exception_30,
	(uint32_t) exception_31
};

idt_entry_t idt_entries[256];
idt_ptr_t idt_ptr;

void idt_init(void)
{
	uint32_t i;

	idt_ptr.base = (uint32_t)idt_entries;
	idt_ptr.limit = sizeof(idt_entry_t) * 256 - 1;

	for (i = 0; i < 32; i++)
		idt_set_entry(i, vectors[i]);

	memset(idt_entries, 0, sizeof(idt_entries));

	asm ("lidt %0" : : "m"(idt_ptr));
}

void idt_set_entry(uint32_t index, uint32_t offset)
{
	idt_entry_t *this = &idt_entries[index];
	this->offset_low = offset & 0xFFFF;
	this->offset_high = (offset >> 16) & 0xFFFF;
	this->reserved = 0;
	this->selector = 0x08;
	this->type = 0x8E;
}

