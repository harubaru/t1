#include <cpu/io.h>

inline void outb(uint16_t port, uint8_t val)
{
	asm volatile ("outb %0, %1" :: "a"(val), "Nd"(port));
}

inline void inb(uint16_t port, uint8_t *val)
{
	asm volatile ("inb %1, %0" : "=a"(*val) : "Nd"(port));
}
