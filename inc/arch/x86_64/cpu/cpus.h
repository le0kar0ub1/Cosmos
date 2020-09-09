/******************************************************************************\
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _ARCH_x86_64_CPU_CPUS_H_
# define _ARCH_x86_64_CPU_CPUS_H_

# include <cosmos.h>
# include <arch/x86_64/system/apic.h>

static inline u32_t x86_64_cpu_get_id(void)
{
	return (apic_get_id());
}

#endif /* !_ARCH_x86_64_CPU_CPUS_H_ */
