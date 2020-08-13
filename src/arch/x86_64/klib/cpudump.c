/********************************************************************************
** 
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include <cosmos.h>
# include <lib/krn.h>
# include <drivers/vga.h>
# include <arch/x86_64/asm.h>
# include <lib/krn.h>
# include <arch/x86_64/interrupts/interrupts.h>

void x86_64_cpudump(void)
{
    asm volatile("int $0x40");
}