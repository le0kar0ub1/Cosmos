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
# include <lib/krn.h>
# include <kernel/mem/memory.h>
# include <kernel/mem/vmm.h>
# include <kernel/mem/kalloc.h>
# include <arch/x86_64/asm.h>

# define RSDP_REVISION_V1 0x0
# define RSDP_REVISION_V2 0x2

physaddr_t prsdp = PHYSNULL;
virtaddr_t vrsdp = NULL;
physaddr_t psdt  = PHYSNULL;
virtaddr_t vsdt  = NULL;
struct sdt_header **acpi_virt_tbl_ptr = NULL;

/*
 * get the rsdp revision
*/
static inline u8_t rsdp_revision(virtaddr_t addr)
{
	return (((struct rsdp_desc_v1 *)addr)->revision);
}

/*
 * Search the RSDP, perform a checksum
*/
static physaddr_t rsdp_research(void)
{
    virtaddr_t start = P2V(0xE0000);
    virtaddr_t end   = P2V(0xFFFFF);

    while (start < end)
    {
	    if (memcmp(start, ACPI_SIG_RSDP, sizeof(ACPI_SIG_RSDP) - 1))
		    break;
	    start = ADD_PTR(start, 0x10);
    }
    if (start >= end)
    	return (PHYSNULL);
    switch (rsdp_revision(start))
    {
	    /* revision V1 */
	    case RSDP_REVISION_V1:
			if (!checksum8((virtaddr_t)start, sizeof(struct rsdp_desc_v1)))
				return (V2P(start));
			break;
        /* revision V2 */
		case RSDP_REVISION_V2:
			if (!checksum8((virtaddr_t)start, sizeof(struct rsdp_desc_v2)))
				return (V2P(start));
			break;
		default:
			return (PHYSNULL);
    }
    return (PHYSNULL);
}

/*
 * Find the ACPI table which match the signature
*/
virtaddr_t acpi_get_table(char const *signature)
{
	u32_t entry = 0x0;

	while (acpi_virt_tbl_ptr[entry])
	{
		if (memcmp(acpi_virt_tbl_ptr[entry]->signature, signature, 4))
			return ((virtaddr_t)acpi_virt_tbl_ptr[entry]);
		entry++;
	}
	return (NULL);
}

/*
 * ACPI map all tables
*/
static virtaddr_t acpi_map_table(void)
{
	u32_t entries = ((struct sdt_header *)vsdt)->lenght;
	entries /= rsdp_revision(vrsdp) == RSDP_REVISION_V1 ? 4 : 8;
	struct sdt_header *current = (struct sdt_header *)vsdt;
	u32_t entry = 0;

	acpi_virt_tbl_ptr = kalloc((entries + 1) * sizeof(virtaddr_t));
	while (entry < entries)
	{
		physaddr_t phys_sdt = rsdp_revision(vrsdp) == RSDP_REVISION_V1 ?
		    (physaddr_t)((struct rsdt *)vsdt)->sdt_phys_addr[entry]:
		    (physaddr_t)((struct xsdt *)vsdt)->sdt_phys_addr[entry];
		if (!phys_sdt)
			break;
		current = kmap_dev(phys_sdt, KCONFIG_MMU_PAGESIZE);
		acpi_virt_tbl_ptr[entry] = current;
		entry++;
	}
	return (NULL);
}

/*
 * Find rsdp, Find sdt, map root sdt
*/
void acpi_init(void)
{
    prsdp = rsdp_research();
    vrsdp = P2V(prsdp);

	if (!prsdp)
		panic("RSDP not found, needed by ACPI");
    if (rsdp_revision(vrsdp) == RSDP_REVISION_V2)
    	psdt = (physaddr_t)((struct rsdp_desc_v2 *)vrsdp)->xsdt_phys_addr;
    else
	    psdt = (physaddr_t)((struct rsdp_desc_v1 *)vrsdp)->rsdt_phys_addr;
	if (!vmm_is_addr_range_mapped(P2V((physaddr_t)psdt), KCONFIG_MMU_PAGESIZE))
		vsdt = kmap_dev(psdt, KCONFIG_MMU_PAGESIZE);
	else 
		vsdt = (virtaddr_t)P2V((physaddr_t)psdt);
	acpi_map_table();
}
