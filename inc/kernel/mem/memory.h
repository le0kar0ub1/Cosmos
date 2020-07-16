/********************************************************************************
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _MEMORY_H_
# define _MEMORY_H_

# include <kernel/def/def.h>

struct pmm_reserved_area
{
    char const *name;
    physaddr_t start;
    physaddr_t end;
};

# define PMM_RESERVE_AREA(n, s, e)                                                               \
    static const struct pmm_reserved_area const _pmm_reserved_area_##n                           \
    __attribute__((__used__, __aligned__(sizeof(void *)), __section__("pmm_reserved_area")))  {  \
        .name = n,                                                                               \
        .start = s,                                                                              \
        .end = e,                                                                                \
    }

# define P2V(x) ((uintptr)x + (uintptr)&__KERNEL_ADDR_TRNS)
# define V2P(x) ((uintptr)x - (uintptr)&__KERNEL_ADDR_TRNS)

#endif /* _MEMORY_H_ */
