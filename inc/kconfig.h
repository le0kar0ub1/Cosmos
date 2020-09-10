/********************************************************************************
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _KCONFIG_H_
# define _KCONFIG_H_

# define KCONFIG_MMU_PAGESIZE 0x1000

# define KCONFIG_MAX_CPUS      0x4

# define KCONFIG_MAXTHREADS   0x20

# define KCONFIG_INITLEVEL    0x9


# define KDEBUG_PRINTF(...)       vga_printf(__VA_ARGS__)
# define KDEBUG_QEMU_PRINTF(...)  uart16650_printf(__VA_ARGS__)

#endif /* !_KCONFIG_H_ */
