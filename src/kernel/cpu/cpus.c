/******************************************************************************\
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include <kernel/cpu/cpus.h>

struct cpu cpus[KCONFIG_MAX_CPUS];

u32_t cpu_get_id(void)
{
	return (ARCH_FUNCTION_MAPPING(cpu_get_id)());
}

struct cpu *cpu_get_desc(void)
{
	return (&cpus[cpu_get_id()]);
}
