#ifndef BOOT_IDT_H
#define BOOT_IDT_H

#include <stdint.h>

typedef struct idt_entry {
        uint16_t offset_low;
        uint16_t selector;
        uint8_t reserved;
        uint8_t type;
        uint16_t offset_high;
} __attribute__((packed)) idt_entry_t;

typedef struct idt_ptr {
        uint16_t limit;
        uint32_t base;
} __attribute__((packed)) idt_ptr_t;

void idt_init(void);
void idt_set_entry(uint32_t index, uint32_t offset);

#endif

