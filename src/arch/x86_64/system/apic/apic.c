/********************************************************************************
** 
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include <cosmos.h>
# include <arch/x86_64/system/apic/apic.h>
# include <arch/x86_64/cpu/cpuid.h>

void apic_init(void)
{
	if (!cpuid_get_feature(CPUID_FEAT_EDX_APIC))
		panic("APIC feature isn't available");
}
