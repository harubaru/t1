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

idt_entry_t idt_entries[256];
idt_ptr_t idt_ptr;

void idt_init(void)
{
	idt_ptr.base = (uint32_t)idt_entries;
	idt_ptr.limit = sizeof(idt_entry_t) * 256 - 1;

	memset(idt_entries, 0, sizeof(idt_entries));

	idt_set_entry(0, (uint32_t)exception_0);
	idt_set_entry(1, (uint32_t)exception_1);
	idt_set_entry(2, (uint32_t)exception_2);
	idt_set_entry(3, (uint32_t)exception_3);
	idt_set_entry(4, (uint32_t)exception_4);
	idt_set_entry(5, (uint32_t)exception_5);
	idt_set_entry(6, (uint32_t)exception_6);
	idt_set_entry(7, (uint32_t)exception_7);
	idt_set_entry(8, (uint32_t)exception_8);
	idt_set_entry(9, (uint32_t)exception_9);
	idt_set_entry(10, (uint32_t)exception_10);
	idt_set_entry(11, (uint32_t)exception_11);
	idt_set_entry(12, (uint32_t)exception_12);
	idt_set_entry(13, (uint32_t)exception_13);
	idt_set_entry(14, (uint32_t)exception_14);
	idt_set_entry(15, (uint32_t)exception_15);
	idt_set_entry(16, (uint32_t)exception_16);
	idt_set_entry(17, (uint32_t)exception_17);
	idt_set_entry(18, (uint32_t)exception_18);
	idt_set_entry(19, (uint32_t)exception_19);
	idt_set_entry(20, (uint32_t)exception_20);
	idt_set_entry(21, (uint32_t)exception_21);
	idt_set_entry(22, (uint32_t)exception_22);
	idt_set_entry(23, (uint32_t)exception_23);
	idt_set_entry(24, (uint32_t)exception_24);
	idt_set_entry(25, (uint32_t)exception_25);
	idt_set_entry(26, (uint32_t)exception_26);
	idt_set_entry(27, (uint32_t)exception_27);
	idt_set_entry(28, (uint32_t)exception_28);
	idt_set_entry(29, (uint32_t)exception_29);
	idt_set_entry(30, (uint32_t)exception_30);
	idt_set_entry(31, (uint32_t)exception_31);
	
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

