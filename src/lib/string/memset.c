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

void *memset(void *x, int c, size_t sz)
{
    if (x)
        for (u32_t i = 0; i < sz; i++)
            ((uchar *)x)[i] = (uchar)c;
    return (x);
}

void *memsetw(void *x, int c, size_t sz)
{
    if (x)
        for (u32_t i = 0; i < sz; i++)
            ((uint16 *)x)[i] = (uint16)c;
    return (x);
}

void *memsetd(void *x, int c, size_t sz)
{
    if (x)
        for (u32_t i = 0; i < sz; i++)
            ((u32_t *)x)[i] = (u32_t)c;
    return (x);
}

void *memsetq(void *x, int c, size_t sz)
{
    if (x)
        for (u32_t i = 0; i < sz; i++)
            ((uint64 *)x)[i] = (uint64)c;
    return (x);
}
