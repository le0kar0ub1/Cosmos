/********************************************************************************
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _KERNEL_MEM_MEMORY_H_
# define _KERNEL_MEM_MEMORY_H_

# include <kernel/def/def.h>
# include <cosmoskcfg.h>

# define P2V(x) ((virtaddr_t)((uintptr_t)x + (uintptr_t)&__KERNEL_ADDR_TRNS))
# define V2P(x) ((physaddr_t)((uintptr_t)x - (uintptr_t)&__KERNEL_ADDR_TRNS))

# define IS_ALIGNED(x, y)   (!(((uintptr_t)x) & (y - 0x1)))
# define IS_PAGE_ALIGNED(x) (IS_ALIGNED(x, KCONFIG_MMU_PAGESIZE))
# define ALIGN(x, y)        ((((uintptr_t)x) + (((uintptr_t)y) - 1)) & ~(((uintptr_t)y) - 1))
# define ALIGN_PAGE(x)      (ALIGN(x, KCONFIG_MMU_PAGESIZE))
# define ROUND_DOWN(x, y)   (((uintptr_t)x) & ~(((uintptr_t)y) - 1))

#endif /* !_KERNEL_MEM_MEMORY_H_ */
