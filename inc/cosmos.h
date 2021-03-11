/******************************************************************************\
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _COSMOS_H_
# define _COSMOS_H_

# include <kernel/def/def.h>
# include <kernel/def/bitfield.h>
# include <kernel/def/ksymtab.h>
# include <kernel/def/access.h>
# include <kernel/def/status.h>
# include <kernel/def/generator.h>
# include <kernel/def/assert.h>
# include <kernel/io/port.h>
# include <kernel/io/mem.h>
# include <kconfig.h>

void kmain(void);
void panic(char const *fmt, ...);

# define cosmos_panic(x) panic(STRINGIFY(x))
# define cosmos_verbose_panic(x, y) panic("%s %s", STRINGIFY(x), y)

enum COSMOS_HOOKS {
    COSMOS_HOOK_BOOT = 0,
    COSMOS_HOOK_PURE = 1,
    COSMOS_HOOK_CORE = 2,
    COSMOS_HOOK_POSTCORE = 3,
    COSMOS_HOOK_DRIVER = 4,
    COSMOS_HOOK_SUBSYS = 5,
    COSMOS_HOOK_COMMAND = 6,
    COSMOS_HOOK_SERVER = 7,
    COSMOS_HOOK_GUI = 8,
    COSMOS_HOOK_LAST = 9
};

#endif /* !_COSMOS_H_ */
