/******************************************************************************\
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include <cosmos.h>

__attribute__((__used__, __aligned__(sizeof(void *)), __section__(".cosmos_config")))
static const struct cosmos_config cosmos_config = {
    .signature = 0xC05A05,
    .mmu_pagesize = KCONFIG_MMU_PAGESIZE,
    .max_cpus = KCONFIG_MAX_CPUS,
    .max_threads = KCONFIG_MAXTHREADS,
    .max_hook = KCONFIG_INITLEVEL
};