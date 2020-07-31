/********************************************************************************
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _DRIVERS_H_
# define _DRIVERS_H_

struct driver
{
    char const *name;
    void (*probe)(void);
    void (*remove)(void);
    void (*suspend)(void);
    void (*resume)(void);
};

# define REGISTER_DRIVER(vname, vprobe, vremove, vsuspend, vresume)  \
    static const struct driver name = {                              \
        .name    = vname,                                            \
        .probe   = vprobe,                                           \
        .remove  = vremove,                                          \
        .suspend = vsuspend,                                         \
        .resume  = vresume,                                          \
    };

char const *driver_name(const struct driver *driver);
void driver_probe(const struct driver *driver);
void driver_remove(const struct driver *driver);
void driver_suspend(const struct driver *driver);
void driver_resume(const struct driver *driver);

#endif /* _DRIVERS_H_ */
