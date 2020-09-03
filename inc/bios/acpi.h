/******************************************************************************
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _BIOS_ACPI_H_
# define _BIOS_ACPI_H_

# include <cosmos.h>

struct rsdp_desc_v1
{
	char signature[8];
	u8_t checksum;
	char oemidi[6];
	u8_t revision;
	u32_t rsdt_addr;
} __packed;

struct rsdp_desc_v2
{
	struct rsdp_desc_v1 rsdpv1;
	u32_t lenght;
	u64_t xsdt_addr;
	u8_t extended_checksum;
	u8_t reserved[3];
} __packed;

void acpi_init(void);

#endif /* !_BIOS_ACPI_H_ */
