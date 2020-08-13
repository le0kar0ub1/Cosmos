/******************************************************************************
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _LIB_STDLIB_H_
# define _LIB_STDLIB_H_

# include <kernel/def/def.h>

s32_t atoi(char const *);
s32_t atoib(char const *, u8_t);
s64_t atol(char const *);
s64_t atolb(char const *, u8_t);

u32_t numberlen(u64_t, u8_t);

#endif /* _LIB_STDLIB_H_ */s