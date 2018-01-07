#include <interrupt/pic.h>

#define PIC_MASTER_CMD  0x0020
#define PIC_MASTER_DATA 0x0021

#define PIC_SLAVE_CMD   0x00A0
#define PIC_SLAVE_DATA  0x00A1

#define PIC_ACK 0x20

#define PIC_MASTER_VECTOR_OFFSET 0x20
#define PIC_SLAVE_VECTOR_OFFSET  0x28

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
	outb(PIC_MASTER_DATA, 0);
	outb(PIC_SLAVE_DATA, 0);
}

void pic_ack(uint8_t irq)
{
	if (irq >= 8)
		outb(PIC_SLAVE_CMD, PIC_ACK);

	outb(PIC_SLAVE_CMD, PIC_ACK);
}
