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

void acpi_madt_init(void)
{
	struct acpi_table_madt *madt =  acpi_get_table("APIC");
	u32_t lenght = madt->header.lenght;
}
