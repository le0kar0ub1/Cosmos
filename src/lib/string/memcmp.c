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

bool memcmp(const void *x, const void *y, size_t sz)
{
    if (x && y)
        for (u32_t i = 0; i < sz; i++)
            if (((uchar *)x)[i] != ((const uchar *)y)[i])
                return (false);
    return (true);
}
