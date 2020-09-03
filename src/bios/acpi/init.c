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
# include <lib/krn.h>
# include <kernel/mem/memory.h>
# include <arch/x86_64/asm.h>

virtaddr_t rsdp = NULL;

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
static virtaddr_t rsdp_research(void)
{
    virtaddr_t start = (virtaddr_t)P2V(0xE0000);
    virtaddr_t end   = (virtaddr_t)P2V(0xFFFFF);

    while (start < end)
    {
	    if (memcmp(start, "RSD PTR ", 0x8))
		    break;
	    start = ADD_PTR(start, 0x10);
    }
    if (start >= end)
    	return (NULL);
    switch (rsdp_revision(start))
    {
	    /* revision V1 */
	    case 0x0:
			if (!checksum8((virtaddr_t)start, sizeof(struct rsdp_desc_v1)))
				return (start);
			break;
        /* revision V2 */
		case 0x2:
			if (!checksum8((virtaddr_t)start, sizeof(struct rsdp_desc_v2)))
				return (start);
			break;
		default:
			return (NULL);
    }
    return (NULL);
}

void acpi_init(void)
{
   rsdp = rsdp_research();
   u8_t rev = rsdp_revision(rsdp);

   KDEBUG_QEMU_PRINTF("%d\n", rev);
}
