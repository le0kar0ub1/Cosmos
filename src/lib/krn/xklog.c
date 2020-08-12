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

void xklog(char const *what, enum vga_color color, char const *fmt, ...)
{
    __builtin_va_list ap;

    vga_printf("[");
    vga_set_color(VGA_BLACK, color);
    vga_printf(what);
    vga_set_color(VGA_BLACK, VGA_WHITE);
    vga_printf("]: ");

    __builtin_va_start(ap, fmt);
    vga_vprintf(fmt, ap);
    __builtin_va_end(ap);
}