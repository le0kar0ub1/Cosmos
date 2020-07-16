/********************************************************************************
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _INITHOOKS_H_
# define _INITHOOKS_H_

typedef void (*inithook_t)(void);

# define __init __attribute__ ((__section__ (".init.text")))

# define __define_inithook(level, fn, id) \
    static const inithook_t __inithook_##fn##id \
    __attribute__((__used__, __section__(".inithook_" level ".text"))) = fn

# define __get_hooklevel(type, level) __##type##level

# define REGISTER_BOOT_INITHOOK(fn)       __define_inithook("0", fn, 0)
# define REGISTER_PURE_INITHOOK(fn)       __define_inithook("1", fn, 1)
# define REGISTER_CORE_INITHOOK(fn)       __define_inithook("2", fn, 2)
# define REGISTER_POSTCORE_INITHOOK(fn)   __define_inithook("3", fn, 3)
# define REGISTER_DRIVER_INITHOOK(fn)     __define_inithook("4", fn, 4)
# define REGISTER_SUBSYS_INITHOOK(fn)     __define_inithook("5", fn, 5)
# define REGISTER_COMMAND_INITHOOK(fn)    __define_inithook("6", fn, 6)
# define REGISTER_SERVER_INITHOOK(fn)     __define_inithook("7", fn, 7)
# define REGISTER_GUI_INITHOOK(fn)        __define_inithook("8", fn, 8)
# define REGISTER_LAST_INITHOOK(fn)       __define_inithook("9", fn, 9)

void run_inithooks(void);
void run_inithooks_bylevel(void);

#endif /* _INITHOOKS_H_ */
