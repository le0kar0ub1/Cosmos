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

bool strcmp(char const *x, char const *y)
{
    if (!x || !y)
        return (false);
    while (*x++ && *y++)
        if (*x != *y)
            return (false);
    return (true);
}

bool strncmp(char const *x, char const *y, size_t sz)
{
    if (!x || !y)
        return (false);
    size_t i = 0;
    for (; x[i] && y[i] && i < sz; i++)
        if (x[i] != y[i])
            return (false);
    if (i != sz)
        return (false);
    return (true);
}