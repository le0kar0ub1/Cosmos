/********************************************************************************
** 
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include <cosmos.h>
# include <bios/acpi.h>

/*
 * Get the acpi madt table
 */
static inline struct acpi_table_madt *acpi_get_madt(void)
{
	return ((struct acpi_table_madt *)acpi_get_table("APIC"));
}

/*
 * Get local apic physical address
 */
physaddr_t acpi_madt_get_phys_loc_apic(void)
{
	return (acpi_get_madt()->loc_apic_addr);
}

/*
 * Get the local apic of the given processor acpi id
 */
static struct acpi_madt_et0_cpu_loc_apic *acpi_madt_get_cpu_loc_apic(u8_t cpu)
{
	struct acpi_table_madt *madt = acpi_get_madt();
	struct acpi_madt_et_flag *et = (struct acpi_madt_et_flag *)ADD_PTR(madt, 0x2C);

	while ((uintptr_t)et < (uintptr_t)ADD_PTR(madt, madt->header.lenght))
	{
		if (et->entry_type == ACPI_MADT_ENTRY_TYPE_0)
			if (((struct acpi_madt_et0_cpu_loc_apic *)et)->acpi_cpu_id == cpu)
				return ((struct acpi_madt_et0_cpu_loc_apic *)et);
		et = ADD_PTR(et, et->record_lenght);
	}
	return (NULL);
}

/*
 * Get the local ioapic of the given ioapic id
 */
static struct acpi_madt_et1_ioapic *acpi_madt_get_ioapic(u8_t ioapicid)
{
	struct acpi_table_madt *madt = acpi_get_madt();
	struct acpi_madt_et_flag *et = (struct acpi_madt_et_flag *)ADD_PTR(madt, 0x2C);

	while ((uintptr_t)et < (uintptr_t)ADD_PTR(madt, madt->header.lenght))
	{
		if (et->entry_type == ACPI_MADT_ENTRY_TYPE_1)
			if (((struct acpi_madt_et1_ioapic *)et)->ioapic_id == ioapicid)
				return ((struct acpi_madt_et1_ioapic *)et);
		et = ADD_PTR(et, et->record_lenght);
	}
	return (NULL);
}
