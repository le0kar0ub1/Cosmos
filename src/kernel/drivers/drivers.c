/********************************************************************************
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include <kernel/drivers/drivers.h>

/*
** Get the given driver name
*/
char const *driver_name(const struct driver *driver)
{
    return (driver->name);
}

/*
** probe the given driver
*/
void driver_probe(const struct driver *driver)
{
    driver->probe();
}

/*
** remove the given driver
*/
void driver_remove(const struct driver *driver)
{
    driver->remove();
}

/*
** suspend the given driver
*/
void driver_suspend(const struct driver *driver)
{
    driver->suspend();
}

/*
** resume the given driver
*/
void driver_resume(const struct driver *driver)
{
    driver->resume();
}
