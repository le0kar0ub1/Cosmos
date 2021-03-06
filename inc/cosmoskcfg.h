/********************************************************************************
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _COSMOSKCFG_H_
# define _COSMOSKCFG_H_

# include <stdint.h>

enum COSMOS_HOOKS {
    COSMOS_HOOK_BOOT = 0,
    COSMOS_HOOK_PURE = 1,
    COSMOS_HOOK_CORE = 2,
    COSMOS_HOOK_POSTCORE = 3,
    COSMOS_HOOK_DRIVER = 4,
    COSMOS_HOOK_SUBSYS = 5,
    COSMOS_HOOK_COMMAND = 6,
    COSMOS_HOOK_SERVER = 7,
    COSMOS_HOOK_GUI = 8,
    COSMOS_HOOK_LAST = 9
};

struct cosmos_config
{
    uint32_t signature;
    uint32_t mmu_pagesize;
    uint32_t max_cpus;
    uint32_t max_threads;
    uint32_t max_hook;    
};

struct cosmos_config *cosmos_get_config(void);
bool cosmos_check_config(void);

extern uint32_t cosmos_signature_hex;
extern char const *cosmos_signature_char;
extern char const *cosmos_signature_asciiart;

# define KCONFIG_MMU_PAGESIZE 0x1000

# define KCONFIG_MAX_CPUS     0x8

# define KCONFIG_MAXTHREADS   0x20

# define KCONFIG_INITLEVEL    0x9


# define KDEBUG_PRINTF(...)       vga_printf(__VA_ARGS__)
# define KDEBUG_QEMU_PRINTF(...)  uart16650_printf(__VA_ARGS__)

#endif /* !_COSMOSKCFG_H_ */
