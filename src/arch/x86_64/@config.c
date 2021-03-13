/******************************************************************************\
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include <cosmos.h>
# include <drivers/uart16650.h>
# include <drivers/vga.h>

__attribute__((__used__, __aligned__(sizeof(void *)), __section__(".cosmos_config")))
static const struct cosmos_config cosmos_config = {
    .signature = 0xC05A05,
    .archsign = "x86_64",
    .mmu_pagesize = 0x1000,
    .max_cpus = 0x8,
    .max_threads = 0x20,
    .printf_uart = uart16650_printf,
    .vprintf_uart = uart16650_vprintf,
    .printf_text = vga_printf,
    .vprintf_text = vga_vprintf,
    .max_hook = COSMOS_HOOK_LAST
};