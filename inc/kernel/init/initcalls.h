/********************************************************************************
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _INITCALLS_H_
# define _INITCALLS_H_

# include <kernel/def/def.h>

typedef void (*initcall_t)(void);

# define __init __attribute__ ((__section__ (".init.text")))

# define __define_initcall(level, fn, id)                                       \
    static const initcall_t __initcall_##fn##id                                 \
    __attribute__((__used__, __section__(".initcall_" level ".text"))) = fn

# define __get_calllevel(level, point) (__initcall##level##point)

# define REGISTER_BOOT_INITCALL(fn)       __define_initcall("0", fn, 0)
# define REGISTER_PURE_INITCALL(fn)       __define_initcall("1", fn, 1)
# define REGISTER_CORE_INITCALL(fn)       __define_initcall("2", fn, 2)
# define REGISTER_POSTCORE_INITCALL(fn)   __define_initcall("3", fn, 3)
# define REGISTER_DRIVER_INITCALL(fn)     __define_initcall("4", fn, 4)
# define REGISTER_SUBSYS_INITCALL(fn)     __define_initcall("5", fn, 5)
# define REGISTER_COMMAND_INITCALL(fn)    __define_initcall("6", fn, 6)
# define REGISTER_SERVER_INITCALL(fn)     __define_initcall("7", fn, 7)
# define REGISTER_GUI_INITCALL(fn)        __define_initcall("8", fn, 8)
# define REGISTER_LAST_INITCALL(fn)       __define_initcall("9", fn, 9)

void run_initcalls(void);
void run_initcall_level(u8_t);

# define run_boot_initcalls()       run_initcall_level(0)
# define run_pure_initcalls()       run_initcall_level(1)
# define run_core_initcalls()       run_initcall_level(2)
# define run_postcore_initcalls()   run_initcall_level(3)
# define run_driver_initcalls()     run_initcall_level(4)
# define run_subsys_initcalls()     run_initcall_level(5)
# define run_command_initcalls()    run_initcall_level(6)
# define run_server_initcalls()     run_initcall_level(7)
# define run_gui_initcalls()        run_initcall_level(8)
# define run_last_initcalls()       run_initcall_level(9)

#endif /* _INITCALLS_H_ */
