/******************************************************************************
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _ARCH_x86_64_SPINLOCK_H_
# define _ARCH_x86_64_SPINLOCK_H_

# include <kernel/def/def.h>
# include <arch/x86_64/asm.h>

/*
** x86 architecture spinlock implementation
*/

typedef u32_t spinlock_t;

# define SPINLOCK_INIT() 0x0

static inline void spinlock_lock(spinlock_t *spinlock)
{
    while (atomic_exchange(spinlock, 1) != 0);
}

static inline void spinlock_unlock(spinlock_t *spinlock)
{
    atomic_exchange(spinlock, 0);
}

#endif /* _ARCH_x86_64_SPINLOCK_H_ */