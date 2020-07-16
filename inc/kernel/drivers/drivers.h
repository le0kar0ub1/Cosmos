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
    char *name;
    void (*probe)(void);
    void (*remove)(void);
    void (*suspend)(void);
    void (*resume)(void);
};

# define REGISTER_DRIVER(name, probe, remove, suspend, resume)  \
    static const struct driver name = {                         \
        .name    = name,                                        \
        .probe   = probe,                                       \
        .remove  = remove,                                      \
        .suspend = suspend,                                     \
        .resume  = resume,                                      \
    };

#endif /* _DRIVERS_H_ */
