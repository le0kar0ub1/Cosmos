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
# include <arch/x86_64/system/ioapic.h>
# include <arch/x86_64/system/apic.h>
# include <arch/x86_64/cpu/cpuid.h>
# include <arch/x86_64/interrupts/interrupts.h>

static volatile u32_t *ioapic = NULL;

/*
 * write the given value to the given register
 */
static void ioapic_write_reg(enum ioapic_reg reg, u32_t val)
{
	*ioapic = reg;
	*((volatile u32_t *)ADD_PTR(ioapic, 0x10)) = val;
}

/*
 * read a value on the given register
 */
static u32_t ioapic_read_reg(enum ioapic_reg reg)
{
	*ioapic = reg;
	return (*((volatile u32_t *)ADD_PTR(ioapic, 0x10)));
}

/*
 * unmask the given vector
 */
void ioapic_unmask_vector(u32_t vector)
{
	union ioapic_entry entry;

	entry.value = 0;
	entry.vector = vector;
	entry.delivery_mode = IOAPIC_DELIVERY_MODE_FIXED;
	entry.polarity = IOAPIC_POLARITY_HIGH;
	entry.trigger_mode = IOAPIC_TRIGGER_EDGE;
	entry.mask = IOAPIC_UNMASK;
	entry.destination_mode = IOAPIC_DEST_MODE_PHYSICAL;
	entry.destination = apic_get_id();
	ioapic_write_reg(IOAPIC_TABLE + (2 * (vector - INT_IRQ0)), entry.low32);
	ioapic_write_reg(IOAPIC_TABLE + (2 * (vector - INT_IRQ0)) + 1, entry.high32);
}

/*
 * mask the given vector
 */
void ioapic_mask_vector(u32_t vector)
{
	union ioapic_entry entry;

	entry.value = 0;
	entry.vector = vector;
	entry.delivery_mode = IOAPIC_DELIVERY_MODE_FIXED;
	entry.polarity = IOAPIC_POLARITY_HIGH;
	entry.trigger_mode = IOAPIC_TRIGGER_EDGE;
	entry.mask = IOAPIC_MASK;
	entry.destination_mode = IOAPIC_DEST_MODE_PHYSICAL;
	entry.destination = apic_get_id();
	ioapic_write_reg(IOAPIC_TABLE +( 2 * (vector - INT_IRQ0)), entry.low32);
	ioapic_write_reg(IOAPIC_TABLE +( 2 * (vector - INT_IRQ0)) + 1, entry.high32);
}


/*
 * map the ioapic
 * mask all the vectors
 */
void ioapic_init(void)
{
	u32_t maxirqs;
	u32_t i = 0;

	ioapic = kmap_dev(IOAPIC_PHYS_BASE_ADDR, KCONFIG_MMU_PAGESIZE);
	assert(ioapic);
	maxirqs = ((union ioapic_version_reg)ioapic_read_reg(IOAPIC_VERSION)).maxirqs;
	while (i < maxirqs)
	{
		ioapic_mask_vector(INT_IRQ0 + i);
		i++;
	}
}

REGISTER_IO_PMM(
	phys_ioapic,
	IOAPIC_PHYS_BASE_ADDR,
	(IOAPIC_PHYS_BASE_ADDR + KCONFIG_MMU_PAGESIZE),
	RW
);
