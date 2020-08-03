/******************************************************************************
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include <kernel/def/def.h>
# include <lib/string.h>

u32_t strlen(char const *s)
{
    if (!s)
        return (0x0);
    u32_t i = 0;
    while (s[i]) i++;
    return (i);
}