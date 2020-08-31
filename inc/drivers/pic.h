/******************************************************************************
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _DRIVER_PIC_H_
# define _DRIVER_PIC_H_

# include <cosmos.h>

#define IRQ0  0x0 // timer
#define IRQ1  0x1 // keyboard
#define IRQ2  0x2 // cascade PIC
#define IRQ3  0x3 // COM2
#define IRQ4  0x4 // COM1
#define IRQ5  0x5 // LPT2
#define IRQ6  0x6 // Floppy disk
#define IRQ7  0x7 // LTP1
#define IRQ8  0x8 // CMOS real-time clock
#define IRQ9  0x9 // Free for peripherals (SCSI / NIC)
#define IRQ10 0xA // Free for peripherals (SCSI / NIC)
#define IRQ11 0xB // Free for peripherals (SCSI / NIC)
#define IRQ12 0xC // PS2 MOUSE
#define IRQ13 0xD // FPU (Floating Point Unit) / Coprocessor / inter-processor
#define IRQ14 0xE // Primary ATA hard disk
#define IRQ15 0xF // Secondary ATA hard disk

void pic_init(void);

#endif /* !_DRIVER_PIC_H_ */