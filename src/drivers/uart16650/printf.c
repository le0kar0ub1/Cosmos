/******************************************************************************
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include <drivers/uart16650.h>
# include <lib/stdio.h>

void uart16650_printf(char const *fmt, ...)
{
    __builtin_va_list ap;
    __builtin_va_start(ap, fmt);
    generic_vprintf(uart16650_szputs, fmt, ap);
    __builtin_va_end(ap);
}

void uart16650_vprintf(char const *fmt, __builtin_va_list ap)
{
    generic_vprintf(uart16650_szputs, fmt, ap);
}