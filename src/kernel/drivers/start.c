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
 * Run the start call's of the driver's name
 */
void driver_start_rununiq(char const *name)
{
    struct driver *mod;
    
    mod = (struct driver *)__cosmos_drivers_start;
    while ((uintptr_t)mod < (uintptr_t)__cosmos_drivers_end) {
        if (!strcmp(mod->name, name) && mod->start) {
            mod->start();
            mod->running = true;
            break;
        }
        mod++;
    }
}

/**
 * Run all the start call's of the given HOOK level
 */
void driver_start_runhook(enum COSMOS_HOOKS hook)
{
    struct driver *mod;
    
    mod = (struct driver *)__cosmos_drivers_start;
    while ((uintptr_t)mod < (uintptr_t)__cosmos_drivers_end) {
        if (mod->hook == hook && mod->start) {
            mod->start();
            mod->running = true;
        }
        mod++;
    }
}