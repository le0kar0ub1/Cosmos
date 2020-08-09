/******************************************************************************\
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include <kernel/io/port.h>
# include <kernel/init/initcalls.h>
# include <drivers/pic.h>
# include <arch/x86_64/interrupts/interrupts.h>
# include <arch/x86_64/asm.h>

# define PIC_EOI 0x20

REGISTER_IO_PORT(
    pic_master_command,
    0x20
);

REGISTER_IO_PORT(
    pic_master_data,
    0x21
);

REGISTER_IO_PORT(
    pic_slave_command,
    0xA0
);

REGISTER_IO_PORT(
    pic_slave_data,
    0xA1
);

/*
** outb & let a delay
*/
static void pic_outb(const struct io_port *port, ushort offset, u8_t data)
{
    outb(port, offset, data);
    io_delay();
}

static inline void pic_eoi(u8_t irq)
{
    if(irq > 0x8)
        outb(&pic_slave_command, 0x0, PIC_EOI);
    outb(&pic_master_command, 0x0, PIC_EOI);
}

static inline void pic_mask(u8_t irq)
{
    u8_t curmask_master = inb(&pic_slave_data, 0x0);
    outb(&pic_master_data, 0x0, curmask_master | (1 << irq));
}

static inline void pic_unmask(u8_t irq)
{
    u8_t curmask_master = inb(&pic_master_data, 0x0);
    outb(&pic_master_data, 0x0, curmask_master & ~(1 << irq));
}


/*
** Init then disable PIC
*/
void pic_init(void)
{
    /* Start init sequence in cascade mode */
    pic_outb(&pic_master_command, 0x0, 0x11);
    pic_outb(&pic_slave_command, 0x0, 0x11);

    /* Set the vector offset */
    pic_outb(&pic_master_data, 0x0, INT_IRQ0);
    pic_outb(&pic_slave_data, 0x0, INT_IRQ0 + 8);

    /* Disable PIC by masking all interrupts */
    pic_outb(&pic_master_data, 0x0, 0xFF);
    pic_outb(&pic_slave_data, 0x0, 0xFF);

    pic_outb(&pic_master_data, 0x0, 0b100);
    pic_outb(&pic_slave_data, 0x0,  0b010);

    /* 80x86 mode, automatic EOI, non buffered */
    pic_outb(&pic_master_data, 0x0, 0b11);
    pic_outb(&pic_slave_data, 0x0,  0b11);

    /* Mask the 8259A PIC's interrupts */
    pic_outb(&pic_master_data, 0x0, 0xFF);
    pic_outb(&pic_slave_data, 0x0,  0xFF);
}

REGISTER_BOOT_INITCALL(pic_init);

#undef PIC_EOI