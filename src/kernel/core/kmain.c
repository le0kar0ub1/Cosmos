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
# include <drivers/uart16650.h>
# include <arch/x86_64/asm.h>

/*
** Kernel main setup
** In fact, due to the kernel architecture,
** we just run preprocessors inithooks -> initcalls by level
*/
void kmain(void)
{
    run_inithooks();
    uart16650_puts("hello world\n");
    while (1);
}