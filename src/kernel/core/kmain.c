/********************************************************************************
** 
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include <cosmos.h>
# include <arch/x86_64/descriptors/idt.h>

void kmain(void);

void kmain(void)
{
    int a = 0;
    a = a / a;
    // idt_init();
    while (1);
}