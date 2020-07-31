/******************************************************************************
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include <drivers/uart1650.h>

void uart1650_printf(char const *fmt, ...)
{
    __builtin_va_list ap;
    __builtin_va_start(ap, fmt);
    generic_vprintf(uart1650_szputs, NULL, fmt, ap);
    __builtin_va_end(ap);
}

void uart1650_vprintf(char const *fmt, __builtin_va_list ap)
{
    generic_vprintf(uart1650_szputs, NULL, fmt, ap);
}