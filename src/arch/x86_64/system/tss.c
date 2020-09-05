
/******************************************************************************
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include <cosmos.h>
# include <arch/x86_64/system/tss.h>
# include <kernel/mem/kalloc.h>

struct x86_64_tss *tss;

/*
** TSS allocation, dynamically allocated
*/
static void tss_allocate(u32_t entries)
{
	tss = kalloc_aligned(entries * sizeof(struct x86_64_tss), 16);
}

/*
** TSS init
*/
void tss_init(u32_t entries)
{
	tss_allocate(entries);
}
