/********************************************************************************
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _BITFIELD_H_
# define _BITFIELD_H_

# include <kernel/def/def.h>

static inline u8_t CLEAR_BYTE(u8_t val, u8_t bit)
{
    return (val & ~(1 << bit));
}

static inline u8_t SET_BYTE(u8_t val, u8_t bit)
{
    return (val | (1 << bit));
}

static inline u16_t CLEAR_WORD(u16_t val, u8_t bit)
{
    return (val & ~(1 << bit));
}

static inline u16_t SET_WORD(u16_t val, u8_t bit)
{
    return (val | (1 << bit));
}

static inline u32_t CLEAR_DOUBLE(u32_t val, u8_t bit)
{
    return (val & ~(1 << bit));
}

static inline u32_t SET_DOUBLE(u32_t val, u8_t bit)
{
    return (val | (1 << bit));
}

static inline u64_t CLEAR_QUAD(u64_t val, u8_t bit)
{
    return (val & ~(1 << bit));
}

static inline u64_t SET_QUAD(u64_t val, u8_t bit)
{
    return (val | (1 << bit));

#endif /* _BITFIELD_H_ */
