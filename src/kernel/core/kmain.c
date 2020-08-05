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
# include <drivers/vga.h>

# include <arch/x86_64/asm.h>

extern char const *cosmos_signature_asciiart;

/*
** Cosmos signature & acquired start
*/
static void helloFromCosmos(void)
{
    vga_set_color(VGA_BLACK, VGA_LIGHT_BLUE);
    vga_puts(cosmos_signature_asciiart);
    vga_set_color(VGA_BLACK, VGA_WHITE);
    vga_puts("\nkernel init routine...");
}

/*
** Kernel main setup
*/
void kmain(void)
{
    run_boot_initcalls();
    uart16650_puts("hello world\n");
    helloFromCosmos();
    while (1);
}