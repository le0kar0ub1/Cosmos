/********************************************************************************
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _ARCH_x86_64_MEM_VMM_H_
# define _ARCH_x86_64_MEM_VMM_H_

# include <cosmos.h>
# include <kernel/mem/memory.h>
# include <kernel/mem/vmm.h>

struct pml4_entry_t
{
    union
    {
        struct
        {
            uintptr_t present : 1;
            uintptr_t rw : 1;
            uintptr_t user : 1;
            uintptr_t wtrough : 1;
            uintptr_t cache : 1;
            uintptr_t accessed : 1;
            uintptr_t dirty : 1;
            uintptr_t size : 1;
            uintptr_t global: 1;
            uintptr_t __unused1 : 3;
            uintptr_t frame : 40;
            uintptr_t __unused2 : 11;
            uintptr_t execDisable : 1;
        };
        uintptr_t value;
    };
};

struct pdp_entry_t
{
    union
    {
        struct
        {
            uintptr_t present : 1;
            uintptr_t rw : 1;
            uintptr_t user : 1;
            uintptr_t wtrough : 1;
            uintptr_t cache : 1;
            uintptr_t accessed : 1;
            uintptr_t dirty : 1;
            uintptr_t size : 1;
            uintptr_t global: 1;
            uintptr_t __unused1 : 3;
            uintptr_t frame : 40;
            uintptr_t Ignored3 : 11;
            uintptr_t execDisable : 1;
        };
        uintptr_t value;
    };
};

struct pd_entry_t
{
    union
    {
        struct
        {
            uintptr_t present : 1;
            uintptr_t rw : 1;
            uintptr_t user : 1;
            uintptr_t wtrough : 1;
            uintptr_t cache : 1;
            uintptr_t accessed : 1;
            uintptr_t dirty : 1;
            uintptr_t size : 1;
            uintptr_t global: 1;
            uintptr_t __unused1 : 3;
            uintptr_t frame : 40;
            uintptr_t Ignored3 : 11;
            uintptr_t execDisable : 1;
        };
        uintptr_t value;
    };
};

struct pt_entry_t
{
    union
    {
        struct
        {
            uintptr_t present : 1;
            uintptr_t rw : 1;
            uintptr_t user : 1;
            uintptr_t wtrough : 1;
            uintptr_t cache : 1;
            uintptr_t accessed : 1;
            uintptr_t dirty : 1;
            uintptr_t size : 1;
            uintptr_t global: 1;
            uintptr_t __unused1 : 3;
            uintptr_t frame : 40;
            uintptr_t Ignored3 : 11;
            uintptr_t execDisable : 1;
        };
        uintptr_t value;
    };
};

struct pt_t
{
    struct pt_entry_t entries[KCONFIG_MMU_PAGESIZE / sizeof(struct pt_entry_t)];
};

static_assert(sizeof(struct pt_t) == KCONFIG_MMU_PAGESIZE);

struct pd_t
{
    struct pd_entry_t entries[KCONFIG_MMU_PAGESIZE / sizeof(struct pd_entry_t)];
};

static_assert(sizeof(struct pd_t) == KCONFIG_MMU_PAGESIZE);

struct pdp_t
{
    struct pdp_entry_t entries[KCONFIG_MMU_PAGESIZE / sizeof(struct pdp_entry_t)];
};

static_assert(sizeof(struct pdp_t) == KCONFIG_MMU_PAGESIZE);

struct pml4_t
{
    struct pml4_entry_t entries[KCONFIG_MMU_PAGESIZE / sizeof(struct pml4_entry_t)];
};

static_assert(sizeof(struct pml4_t) == KCONFIG_MMU_PAGESIZE);

bool x86_64_vmm_is_mapped(virtaddr_t virt);
physaddr_t x86_64_vmm_get_mapped_frame(virtaddr_t virt);
result_t x86_64_vmm_map_phys(virtaddr_t virt, physaddr_t phys, mmap_attrib_t attrib);
result_t x86_64_vmm_map_virt(virtaddr_t virt, mmap_attrib_t attrib);
void x86_64_vmm_unmap(virtaddr_t virt, munmap_attrib_t attrib);
void x86_64_vmm_init(void);

#endif /* !_ARCH_x86_64_MEM_VMM_H_ */
