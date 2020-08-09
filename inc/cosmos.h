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
# include <kernel/drivers/drivers.h>
# include <kconfig.h>

void panic(char const *fmt, ...);
void kmain(void);
void boot_hook(void);

#endif /* _COSMOS_H_ */