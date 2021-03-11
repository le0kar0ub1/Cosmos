/********************************************************************************
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _KERNEL_DRIVERS_H_
# define _KERNEL_DRIVERS_H_

# include <cosmos.h>
# include <kernel/io/mem.h>

struct driver
{
    char const name[32];
    char const desc[128];
    enum COSMOS_HOOKS hook;
    bool initialized;
    bool running;
    void (*probe)(void);
    void (*remove)(void);
    void (*reset)(void);
    void (*start)(void);
    void (*stop)(void);
    void (*debug)(void);
    struct memory_area pmmarea;
    void *data; // currently unused , will be usefull when we will have to pass static data to our kernel
};

# define REGISTER_DRIVER(vname, vdesc, vhook, vprobe, vremove, vreset, vstart, vstop, vdebug, vpmmarea, vdata)      \ 
    __attribute__((__used__, __aligned__(sizeof(void *)), __section__(".cosmos_drivers")))                          \
    static const struct driver vname = {                                                                            \
        .name    = #vname,                                                                                          \
        .desc    = vdesc,                                                                                           \
        .hook    = vhook,                                                                                           \
        .probe   = vprobe,                                                                                          \
        .remove  = vremove,                                                                                         \
        .reset   = vreset,                                                                                          \
        .start   = vstart,                                                                                          \
        .stop    = vstop,                                                                                           \
        .debug   = vdebug,                                                                                          \
        .pmmarea = vpmmarea,                                                                                        \
        .data    = vdata,                                                                                           \
        .running = false,                                                                                           \
        .initialized = false                                                                                        \
    };

void driver_probe_rununiq(char const *name);
void driver_probe_runhook(enum COSMOS_HOOKS hook);

void driver_remove_rununiq(char const *name);
void driver_remove_runhook(enum COSMOS_HOOKS hook);

void driver_reset_rununiq(char const *name);
void driver_reset_runhook(enum COSMOS_HOOKS hook);

void driver_start_rununiq(char const *name);
void driver_start_runhook(enum COSMOS_HOOKS hook);

void driver_stop_rununiq(char const *name);
void driver_stop_runhook(enum COSMOS_HOOKS hook);

void driver_debug_rununiq(char const *name);

bool driver_is_initialized_rununiq(char const *name);
bool driver_is_running_rununiq(char const *name);

struct driver *driver_fetch(char const *name);

#endif /* !_KERNEL_DRIVERS_H_ */
