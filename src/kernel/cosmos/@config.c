/******************************************************************************\
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include <cosmos.h>
# include <lib/string.h>

extern struct cosmos_config __cosmos_config_start[];
extern uintptr_t __cosmos_config_end[];

struct cosmos_config *cosmos_get_config(void)
{
    return ((struct cosmos_config *)__cosmos_config_start);
}

bool cosmos_check_config(void)
{
    return (((struct cosmos_config *)__cosmos_config_start)->signature == cosmos_signature_hex);
}