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
# include <kernel/mem/kalloc.h>
# include <kernel/io/spinlock.h>
# include <lib/string.h>

static spinlock_t lock = SPINLOCK_UNLOCKED();

/*
** Call the arch-dependant mmap to map X page
*/
virtaddr_t vmm_mmap(virtaddr_t virt, size_t sz, mmap_attrib_t attrib)
{
    virtaddr_t keep = virt;

    assert(IS_PAGE_ALIGNED(virt));
    assert(IS_PAGE_ALIGNED(sz));

    spinlock_lock(&lock);
    while ((uintptr_t)virt < (uintptr_t)ADD_PTR(keep, sz))
    {
        if (RESULT_IS_ERR(ARCH_FUNCTION_MAPPING(vmm_map_virt)(virt, attrib))) {
            spinlock_unlock(&lock);
            return (NULL);
        }
        virt = ADD_PTR(virt, KCONFIG_MMU_PAGESIZE);
    }
    spinlock_unlock(&lock);
    return (keep);
}

/*
** Call the arch-dependant unmap to unmap X page
*/
void vmm_unmap(virtaddr_t virt, size_t sz, mmap_attrib_t attrib)
{
    virtaddr_t keep = virt;

    assert(IS_PAGE_ALIGNED(virt));
    assert(IS_PAGE_ALIGNED(sz));

    spinlock_lock(&lock);
    while ((uintptr_t)virt < (uintptr_t)ADD_PTR(keep, sz))
    {
        ARCH_FUNCTION_MAPPING(vmm_unmap)(virt, attrib);
        virt = ADD_PTR(virt, KCONFIG_MMU_PAGESIZE);
    }
    spinlock_unlock(&lock);
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
    spinlock_lock(&lock);
    while ((uintptr_t)virt < (uintptr_t)ADD_PTR(keep, size))
    {
        status = ARCH_FUNCTION_MAPPING(vmm_map_phys)(virt, phys, attrib);
        if (RESULT_IS_ERR(status))
        {
            if (RESULT_ERR(status) == ERR_VMM_ALREADY_MAPPED)
                ARCH_FUNCTION_MAPPING(vmm_unmap)(virt, MUNMAP_DEFAULT);
            spinlock_unlock(&lock);
            return (NULL);
        }
        phys = (uintptr_t)ADD_PTR(phys, KCONFIG_MMU_PAGESIZE);
        virt = (virtaddr_t)ADD_PTR(virt, KCONFIG_MMU_PAGESIZE);
    }
    spinlock_unlock(&lock);
    return (keep);
}

/*
 * Is the given address range mapped ?
*/
bool vmm_is_addr_range_mapped(virtaddr_t virt, size_t size)
{
	virtaddr_t start = (virtaddr_t)ROUND_DOWN(virt, KCONFIG_MMU_PAGESIZE);
	virtaddr_t end   = (virtaddr_t)ROUND_DOWN(ADD_PTR(virt, size), KCONFIG_MMU_PAGESIZE);

	while ((uintptr_t)start <= (uintptr_t)end)
	{
		if (!vmm_is_mapped(start))
			return (false);
		ADD_PTR(start, KCONFIG_MMU_PAGESIZE);
	}
	return (true);
}

physaddr_t vmm_get_mapped_frame(virtaddr_t virt)
{
    return (ARCH_FUNCTION_MAPPING(vmm_get_mapped_frame)(virt));
}

bool vmm_is_mapped(virtaddr_t virt)
{
    return (ARCH_FUNCTION_MAPPING(vmm_is_mapped)(virt));
}

/*
 * Return the PA which match the VA
*/ 
physaddr_t vmm_get_paddr(virtaddr_t virt)
{
	physaddr_t phys = PHYSNULL;

	if (!vmm_is_mapped((virtaddr_t)ROUND_DOWN(virt, KCONFIG_MMU_PAGESIZE)))
		return (PHYSNULL);
	physaddr_t frame = vmm_get_mapped_frame(virt);
	if (frame == PHYSNULL)
		return (PHYSNULL);
	return (frame + ((physaddr_t)virt % KCONFIG_MMU_PAGESIZE));
}

void vmm_init(void)
{
    kalloc_init();
}

/*
** Can't be a initcall()
** we are calling the kalloc_init() which need arch VMM initcall 
*/
