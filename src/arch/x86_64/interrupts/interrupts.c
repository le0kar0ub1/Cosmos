/******************************************************************************\
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include <arch/x86_64/interrupts/interrupts.h>
# include <arch/x86_64/asm.h>

/*
 * Enable interrupts interface
 */
void interrupts_enable(void)
{
	sti();
}

/*
 * Disable interrupt interface
 */
void interrupts_disable(void)
{
	cli();
}

/*
 * Are interrupts enabled interface
 */
bool are_interrupts_enabled(void)
{
	return (rflags_get().ief);
}

/*
 * Wait For Interrupt interface
 * inspired by the ARM instruction, seems like a good name
 */
void wfi(void)
{
	hlt();
}
