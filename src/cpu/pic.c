#include <cpu/pic.h>

#define PIC_MASTER_CMD  0x0020
#define PIC_MASTER_DATA 0x0021

#define PIC_SLAVE_CMD   0x00A0
#define PIC_SLAVE_DATA  0x00A1

#define PIC_ACK 0x20

#define PIC_MASTER_VECTOR_OFFSET 0x20
#define PIC_SLAVE_VECTOR_OFFSET  0x28

uint16_t irq_mask = 0xFFFB; // 3rd bit set for Slave PIC

#define IRQ_MASK_MASTER (uint8_t)(irq_mask & 0xFF)
#define IRQ_MASK_SLAVE (uint8_t)((irq_mask >> 8) & 0xFF)

void pic_init(void)
{
	/* Initialize PIC */
	outb(PIC_MASTER_CMD, 0x11);
	outb(PIC_MASTER_CMD, 0x11);

	/* Setup PIC Master and Slave vector offset */
	outb(PIC_MASTER_DATA, PIC_MASTER_VECTOR_OFFSET);
	outb(PIC_SLAVE_DATA, PIC_SLAVE_VECTOR_OFFSET);

	/* Make Master acknowledge the fact he has a slave PIC */
	outb(PIC_MASTER_DATA, 4);
	outb(PIC_SLAVE_DATA, 2); /* tells slave pic it's cascade identity */

	/* Enabling 8086 mode */
	outb(PIC_MASTER_DATA, 1);
	outb(PIC_SLAVE_DATA, 1);

	/* Reset masks */
	outb(PIC_MASTER_DATA, IRQ_MASK_MASTER);
	outb(PIC_SLAVE_DATA, IRQ_MASK_SLAVE);
}

void pic_enable_irq(uint8_t irq)
{
	irq_mask = irq_mask & ~(1 << irq); // clear bit that the IRQ is on

	if (irq >= 8) {
		outb(PIC_SLAVE_DATA, IRQ_MASK_SLAVE);
	} else {
		outb(PIC_MASTER_DATA, IRQ_MASK_MASTER);
	}
}

void pic_disable_irq(uint8_t irq)
{
	irq_mask |= (1 << irq); // set bit that the IRQ is on

	if (irq >= 8) {
		outb(PIC_SLAVE_DATA, IRQ_MASK_SLAVE);
	} else {
		outb(PIC_MASTER_DATA, IRQ_MASK_MASTER);
	}
}

void pic_ack(uint8_t irq)
{
	if (irq >= 8)
		outb(PIC_SLAVE_CMD, PIC_ACK);

	outb(PIC_MASTER_CMD, PIC_ACK);
}
