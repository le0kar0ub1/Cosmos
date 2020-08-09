/********************************************************************************
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include <kernel/init/inithooks.h>
# include <kernel/init/initcalls.h>
# include <drivers/vga.h>

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

void boot_hook(void)
{
    run_boot_initcalls();
    helloFromCosmos();
}