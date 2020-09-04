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
# include <lib/string.h>
# include <drivers/uart16650.h>

static inline struct acpi_table_fadt *acpi_get_fadt(void)
{
	return ((struct acpi_table_fadt *)acpi_get_table(ACPI_SIG_FADT));
}

void acpi_enable(void)
{
	acpi_get_fadt()->acpi_enable = true;
}

void acpi_disable(void)
{
	acpi_get_fadt()->acpi_disable = true;
}
