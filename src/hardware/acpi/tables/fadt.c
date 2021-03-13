/********************************************************************************
** 
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include <cosmos.h>
# include <kernel/io/port.h>
# include <hardware/acpi.h>
# include <lib/string.h>

/*
 * Port will be update in runtime
*/
REGISTER_IO_PORT(
	acpi_smi_cmd,
	0x0
);

static inline struct acpi_table_fadt *acpi_get_fadt(void)
{
	return ((struct acpi_table_fadt *)acpi_get_table(ACPI_SIG_FADT));
}

void acpi_enable(void)
{
	outb(&acpi_smi_cmd, acpi_get_fadt()->acpi_enable, 0x0);
}

void acpi_disable(void)
{
	outb(&acpi_smi_cmd, acpi_get_fadt()->acpi_disable, 0x0);
}

void acpi_fadt_init(void)
{
	acpi_smi_cmd.port = (u16_t)acpi_get_fadt()->smi_command;
}
