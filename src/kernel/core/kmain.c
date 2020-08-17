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
# include <lib/krn.h>

/*
** Kernel main setup.
** In fact, due to the kernel architecture,
** we just run preprocessors inithooks -> initcalls by level
** So the init code is in src/kernel/core/hooks
*/
void kmain(void)
{
    run_inithooks();
    
    kalloc_dump();
    // hlt();

    char *test = kalloc(0x10);
    // uart16650_printf("this %#X\n", kalloc(0x10));
    kalloc(0x10);
    kalloc_dump();
    hlt();
    for (int a = 0; a < 0X10; a++)
        test[a] = a + 0x41;
    test[0xE] = 0X0;
    uart16650_printf("%s\n", test);
    
    uart16650_puts("Cosmos initialization done.\n");
    // cpudump();
    while (1);
}