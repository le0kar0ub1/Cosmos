/********************************************************************************
** 
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include <cosmos.h>
# include <arch/x86_64/interrupts/interrupts.h>

void apic_error_interrupt_handler(struct interrupt_frame *frame __unused)
{
	panic("APIC error handler");
}
