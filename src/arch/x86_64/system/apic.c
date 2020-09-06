/********************************************************************************
** 
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include <cosmos.h>
# include <kernel/mem/kalloc.h>
# include <kernel/io/mem.h>
# include <arch/x86_64/system/apic.h>
# include <arch/x86_64/cpu/cpuid.h>

static volatile u32_t *apic = NULL;

/*
 * write the given value to the given register
 */
static void apic_write_reg(enum apic_reg reg, u32_t val)
{
	*((volatile u32_t *)ADD_PTR(apic, reg)) = val;
}

/*
 * read a value on the given register
 */
static u32_t apic_read_reg(enum apic_reg reg)
{
	return (*((volatile u32_t *)ADD_PTR(apic, reg)));
}

void apic_init(void)
{
	if (!cpuid_get_feature(CPUID_FEAT_EDX_APIC))
		panic("APIC feature isn't available");
	apic = kmap_dev(APIC_PHYS_BASE_ADDR, KCONFIG_MMU_PAGESIZE);
	assert(apic);
}

REGISTER_IO_PMM(
	phys_apic,
	APIC_PHYS_BASE_ADDR,
	(APIC_PHYS_BASE_ADDR + KCONFIG_MMU_PAGESIZE),
	RW
);
