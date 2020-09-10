/******************************************************************************\
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _KERNEL_CPU_CPUS_H_
# define _KERNEL_CPU_CPUS_H_

# include <cosmos.h>
# include ARCH_HEADER(cpu/cpus.h)

struct cpu
{
	bool started;
	u32_t id;
} __packed;

u32_t cpu_get_id(void);
struct cpu *cpu_get_desc(void);

#endif /* !_KERNEL_CPU_CPUS_H_ */
