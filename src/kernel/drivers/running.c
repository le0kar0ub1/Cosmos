/********************************************************************************
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include <kernel/drivers/drivers.h>
# include <lib/string.h>

extern struct driver __cosmos_drivers_start[];
extern struct driver __cosmos_drivers_end[];

/**
 * Is the driver running
 */
bool driver_is_running_rununiq(char const *name)
{
    struct driver *mod;
    
    mod = (struct driver *)__cosmos_drivers_start;
    while ((uintptr_t)mod < (uintptr_t)__cosmos_drivers_end) {
        if (!strcmp(mod->name, name)) {
            return (mod->running);
        }
        mod++;
    }
    return (false);
}