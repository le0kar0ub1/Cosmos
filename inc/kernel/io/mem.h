/********************************************************************************
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _IOMEM_H_
# define _IOMEM_H_

# include <kernel/def/def.h>

static inline u8_t read8(virtaddr_t addr)
{
    return (*((volatile u8_t *)(addr)));
}

static inline u16_t read16(virtaddr_t addr)
{
    return (*((volatile u16_t *)(addr)));
}

static inline u32_t read32(virtaddr_t addr)
{
    return (*((volatile u32_t *)(addr)));
}

static inline u64_t read64(virtaddr_t addr)
{
    return (*((volatile u64_t *)(addr)));
}

static inline void write8(virtaddr_t addr, u8_t value)
{
    *((volatile u8_t *)(addr)) = value;
}

static inline void write16(virtaddr_t addr, u16_t value)
{
    *((volatile u16_t *)(addr)) = value;
}

static inline void write32(virtaddr_t addr, u32_t value)
{
    *((volatile u32_t *)(addr)) = value;
}

static inline void write64(virtaddr_t addr, u64_t value)
{
    *((volatile u64_t *)(addr)) = value;
}

#endif /* _IOMEM_H_ */
