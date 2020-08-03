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

void *memcpy(void *dest, const void *src, size_t sz)
{
    if (dest && src)
        for (u32_t i = 0; i < sz; i++)
            ((uchar *)dest)[i] = ((const uchar *)src)[i];
    return (dest);
}
