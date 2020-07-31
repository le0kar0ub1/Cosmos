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
# include <kernel/init/inithooks.h>
# include <kernel/init/initcalls.h>

void kmain(void);

void kmain(void)
{
    run_boot_initcalls();
    uart16650_puts("hello world");
    while (1);
}