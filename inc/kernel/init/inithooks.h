/********************************************************************************
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _KERNEL_INIT_INITHOOKS_H_
# define _KERNEL_INIT_INITHOOKS_H_

typedef void (*inithook_t)(void);

# define __init __attribute__ ((__section__ (".init.text")))

# define __define_inithook(level, fn, id) \
    static const inithook_t __inithook_##fn##id \
    __attribute__((__used__, __section__(".inithook_" level ".text"))) = fn

# define __get_hooklevel(type, level) __##type##level

# define REGISTER_BOOT_INITHOOK(fn)       __define_inithook("0", fn, COSMOS_HOOK_BOOT)
# define REGISTER_PURE_INITHOOK(fn)       __define_inithook("1", fn, COSMOS_HOOK_PURE)
# define REGISTER_CORE_INITHOOK(fn)       __define_inithook("2", fn, COSMOS_HOOK_CORE)
# define REGISTER_POSTCORE_INITHOOK(fn)   __define_inithook("3", fn, COSMOS_HOOK_POSTCORE)
# define REGISTER_DRIVER_INITHOOK(fn)     __define_inithook("4", fn, COSMOS_HOOK_DRIVER)
# define REGISTER_SUBSYS_INITHOOK(fn)     __define_inithook("5", fn, COSMOS_HOOK_SUBSYS)
# define REGISTER_COMMAND_INITHOOK(fn)    __define_inithook("6", fn, COSMOS_HOOK_COMMAND)
# define REGISTER_SERVER_INITHOOK(fn)     __define_inithook("7", fn, COSMOS_HOOK_SERVER)
# define REGISTER_GUI_INITHOOK(fn)        __define_inithook("8", fn, COSMOS_HOOK_GUI)
# define REGISTER_LAST_INITHOOK(fn)       __define_inithook("9", fn, COSMOS_HOOK_LAST)

void run_inithooks(void);
void run_inithooks_bylevel(void);

#endif /* !_KERNEL_INIT_INITHOOKS_H_ */
