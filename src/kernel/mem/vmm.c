/********************************************************************************
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include <cosmos.h>
# include <kernel/mem/pmm.h>
# include <kernel/mem/vmm.h>
# include <arch/x86_64/asm.h>
# include <lib/string.h>

/*
** Call the arch-dependant mmap to map X page
*/
virtaddr_t vmm_mmap(virtaddr_t virt, size_t sz, mmap_attrib_t attrib)
{
    virtaddr_t keep = virt;

    assert(IS_PAGE_ALIGNED(virt));
    assert(IS_PAGE_ALIGNED(sz));

    while ((uintptr)virt < (uintptr)ADD_TO_PTR(keep, sz))
    {
        if (RESULT_IS_ERR(ARCH_FUNCTION_MAPPING(vmm_map_virt)(virt, attrib)))
            return (NULL);
        virt = ADD_TO_PTR(virt, KCONFIG_MMU_PAGESIZE);
    }
    return (keep);
}

/*
** Call the arch-dependant mmap to unmap X page
*/
void vmm_unmap(virtaddr_t virt, size_t sz, mmap_attrib_t attrib)
{
    virtaddr_t keep = virt;

    assert(IS_PAGE_ALIGNED(virt));
    assert(IS_PAGE_ALIGNED(sz));

    while ((uintptr)virt < (uintptr)ADD_TO_PTR(keep, sz))
    {
        ARCH_FUNCTION_MAPPING(vmm_unmap)(virt, attrib);
        virt = ADD_TO_PTR(virt, KCONFIG_MMU_PAGESIZE);
    }
}

/*
** Call the arch-dependant to map a know virtual & physical address
*/
virtaddr_t vmm_mmap_dev(virtaddr_t virt, physaddr_t phys, size_t size, mmap_attrib_t attrib)
{
    virtaddr_t keep = virt;
    result_t status;

    assert(IS_PAGE_ALIGNED(virt));
    assert(IS_PAGE_ALIGNED(phys));
    assert(IS_PAGE_ALIGNED(size));

    if (!virt || !phys)
        return (NULL);
    while ((uintptr)virt < (uintptr)ADD_TO_PTR(keep, size))
    {
        status = ARCH_FUNCTION_MAPPING(vmm_map_phys)(virt, phys, attrib);
        if (RESULT_IS_ERR(status))
        {
            if (RESULT_ERR(status) == ERR_VMM_ALREADY_MAPPED)
                ARCH_FUNCTION_MAPPING(vmm_unmap)(virt, MUNMAP_DEFAULT);
            return (NULL);
        }
        phys = (uintptr)ADD_TO_PTR(phys, KCONFIG_MMU_PAGESIZE);
        virt = (virtaddr_t)ADD_TO_PTR(virt, KCONFIG_MMU_PAGESIZE);
    }
    return (keep);
}

bool vmm_is_mapped(virtaddr_t virt)
{
    return (ARCH_FUNCTION_MAPPING(vmm_is_mapped)(virt));
}

void vmm_init(void)
{
    // kalloc_init();
}

/*
** Can't be a initcall()
** we are calling the kalloc_init() which need arch VMM initcall 
*/