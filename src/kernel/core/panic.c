/********************************************************************************
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include <kernel/def/def.h>
# include <drivers/vga.h>

__noreturn
void panic(char const *fmt, ...)
{
    vga_printf("Kernel panicked:\n    ");
    __builtin_va_list ap;
    __builtin_va_start(ap, fmt);
    vga_vprintf(fmt, ap);
    __builtin_va_end(ap);
    while (1);
}