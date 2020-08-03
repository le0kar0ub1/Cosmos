/******************************************************************************
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include <kernel/def/def.h>
# include <lib/stdlib.h>

u32_t numberlen(u32_t n, u8_t base)
{
    u32_t len = 0x0;

    while (n >= base) {
        n /= base;
        len++;
    }
    return (len);
}