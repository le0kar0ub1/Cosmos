/********************************************************************************
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include <cosmos.h>
# include <arch/x86_64/mem/vmm.h>
# include <kernel/mem/pmm.h>
# include <arch/x86_64/asm.h>
# include <lib/string.h>

/*
** If there is no recursive mapping all these functions will fucked up.
** Assuming that's not the case.
** This functions are usable only in this file.
** The recursive mapping is on the index 510 of the pml4, yes, weird.
*/

/*
** Get physical pml4 address
*/
static inline struct pml4_t *get_pml4(void)
{
    return (
        (struct pml4_t *)0xffffff7fbfdfe000ul
    );
}

/*
** Get physical pdp address
*/
static inline struct pdp_t *get_pdp(u32_t pml4idx)
{
    return (
        (struct pdp_t *)((0xffffff7fbfdfe000ul & ~((1ul << 21ul) - 1)) |
        (((uintptr_t)pml4idx & 0x1FF) << 12ul)
    ));
}

/*
** Get physical pd address
*/
static inline struct pd_t *get_pd(u32_t pml4idx, u32_t pdpidx)
{
    return (
        (struct pd_t *)((0xffffff7fbfdfe000ul & ~((1ul << 30ul) - 1)) |
        (((uintptr_t)pml4idx & 0x1FF) << 21ul) |
        (((uintptr_t)pdpidx & 0x1FF) << 12ul)
    ));
}

/*
** Get physical pt address
*/
static inline struct pt_t *get_pt(u32_t pml4idx, u32_t pdpidx, u32_t pdidx)
{
    return (
        (struct pt_t *)((0xffffff7fbfdfe000ul & ~((1ul << 39ul) - 1)) |
        (((uintptr_t)pml4idx & 0x1FF) << 30ul) |
        (((uintptr_t)pdpidx & 0x1FF) << 21ul) |
        (((uintptr_t)pdidx & 0x1FF) << 12ul)
    ));
}

/*
** Idx/addr pagination get
*/
static inline u32_t virt2pml4Idx(virtaddr_t va)
{
    return (((uintptr_t)(va) >> 39) & 0x1FF);
}

static inline u32_t virt2pdpIdx(virtaddr_t va)
{
    return (((uintptr_t)(va) >> 30) & 0x1FF);
}

static inline u32_t virt2pdIdx(virtaddr_t va)
{
    return (((uintptr_t)(va) >> 21) & 0x1FF);
}

static inline u32_t virt2ptIdx(virtaddr_t va)
{
    return (((uintptr_t)(va) >> 12) & 0x1FF);
}

static inline virtaddr_t idx2addr(u32_t pml4idx, u32_t pdpidx, u32_t pdidx, u32_t ptidx)
{
    uintptr_t addr = ((uintptr_t)pml4idx << 39ul) | ((uintptr_t)pdpidx << 30ul) | 
                   ((uintptr_t)pdidx << 21ul)   | ((uintptr_t)ptidx << 12ul);

    if ((bool)(addr & (1ul << 48ul)) == 1)
        addr |= ((1ul << 12ul) - 1) << 48ul;
    return ((virtaddr_t)addr);
}

/*
** is the given page mapped ?
*/
bool x86_64_vmm_is_mapped(virtaddr_t virt)
{
    assert(IS_PAGE_ALIGNED(virt));
    if (
        !get_pml4()->entries[virt2pml4Idx(virt)].present ||
        !get_pdp(virt2pml4Idx(virt))->entries[virt2pdpIdx(virt)].present ||
        !get_pd(virt2pml4Idx(virt), virt2pdpIdx(virt))->entries[virt2pdIdx(virt)].present
    )
        return (false);
    return (
        get_pt(virt2pml4Idx(virt), virt2pdpIdx(virt), virt2pdIdx(virt))->entries[virt2ptIdx(virt)].present
    );
}

/*
** get the mapped frame from the given page
*/
physaddr_t x86_64_vmm_get_mapped_frame(virtaddr_t virt)
{
    assert(IS_PAGE_ALIGNED(virt));
    if (
        !get_pml4()->entries[virt2pml4Idx(virt)].present ||
        !get_pdp(virt2pml4Idx(virt))->entries[virt2pdpIdx(virt)].present ||
        !get_pd(virt2pml4Idx(virt), virt2pdpIdx(virt))->entries[virt2pdIdx(virt)].present
    )
        return (0x0);
    return (
        get_pt(virt2pml4Idx(virt), virt2pdpIdx(virt), virt2pdIdx(virt))->entries[virt2ptIdx(virt)].frame << 0xC
    );
}

/*
** map a page on a frame
*/
result_t x86_64_vmm_map_phys(virtaddr_t virt, physaddr_t phys, mmap_attrib_t attrib)
{
    struct pml4_entry_t *pml4e;
    struct pdp_entry_t *pdpe;
    struct pd_entry_t *pde;
    struct pt_entry_t *pte;
    struct pdp_t *pdp;
    struct pd_t *pd;
    struct pt_t *pt;

    assert(IS_PAGE_ALIGNED(virt));
    assert(IS_PAGE_ALIGNED(phys));

    pml4e = &(get_pml4()->entries[virt2pml4Idx(virt)]);
    pdp = get_pdp(virt2pml4Idx(virt));
    if (!pml4e->present) {
        UNWRAP_OR_RAISE(
            pml4e->value,
            pmm_alloc_frame()
        );
        pml4e->present = true;
        pml4e->user = true;
        pml4e->rw = true;
        pml4e->accessed = false;
        invlpg(pdp);
        memset(pdp, 0x0, KCONFIG_MMU_PAGESIZE);
    }

    pdpe = &(pdp->entries[virt2pdpIdx(virt)]);
    pd = get_pd(virt2pml4Idx(virt), virt2pdpIdx(virt));
    if (!pdpe->present) {
        UNWRAP_OR_RAISE(
            pdpe->value,
            pmm_alloc_frame()
        );
        pdpe->present = true;
        pdpe->user = true;
        pdpe->rw = true;
        pdpe->accessed = false;
        invlpg(pd);
        memset(pd, 0x0, KCONFIG_MMU_PAGESIZE);
    }

    pde = &(pd->entries[virt2pdIdx(virt)]);
    pt = get_pt(virt2pml4Idx(virt), virt2pdpIdx(virt), virt2pdIdx(virt));
    if (!pde->present) {
        UNWRAP_OR_RAISE(
            pde->value,
            pmm_alloc_frame()
        );
        pde->present = true;
        pde->user = true;
        pde->rw = true;
        pde->accessed = false;
        invlpg(pt);
        memset(pt, 0x0, KCONFIG_MMU_PAGESIZE);
    }

    pte = &(pt->entries[virt2ptIdx(virt)]);
    if (pte->present) {
        if (pte->frame && MASK_MMAP_REMAP(attrib))
            pmm_free_frame(pte->frame << 0xC);
        else
            ERR_PROPAGATION(ERR_VMM_ALREADY_MAPPED);
    }
    pte->value = phys;
    pte->present = true;
    pte->rw = MASK_MMAP_WRITE(attrib);
    pte->user = MASK_MMAP_USER(attrib);
    pte->accessed = false;
    pte->dirty = 0x0;
    invlpg(virt);
    OK_PROPAGATION(OK);
}

/*
** map a page on any frame
*/
result_t x86_64_vmm_map_virt(virtaddr_t virt, mmap_attrib_t attrib)
{
    assert(IS_PAGE_ALIGNED(virt));
    physaddr_t phys;
    UNWRAP_OR_RAISE(
        phys,
        pmm_alloc_frame()
    );
    result_t status;
    if (!phys)
        ERR_PROPAGATION(ERR_PMM_OUT_OF_MEMORY);
    status = x86_64_vmm_map_phys(virt, phys, attrib);
    if (RESULT_IS_ERR(status))
        pmm_free_frame(phys);
    return (status);
}

/*
** Unmap the given page
*/
void x86_64_vmm_unmap(virtaddr_t virt, munmap_attrib_t attrib)
{
    assert(IS_PAGE_ALIGNED(virt));
    struct pml4_entry_t *pml4e;
    struct pdp_entry_t *pdpe;
    struct pd_entry_t *pde;
    struct pt_entry_t *pte;

    pml4e = &(get_pml4()->entries[virt2pml4Idx(virt)]);
    if (!pml4e->present)
        return;
    pdpe = &(get_pdp(virt2pml4Idx(virt))->entries[virt2pdpIdx(virt)]);
    if (!pdpe->present)
        return;
    pde = &(get_pd(virt2pml4Idx(virt), virt2pdpIdx(virt))->entries[virt2pdIdx(virt)]);
    if (!pde->present)
        return;
    pte = &(get_pt(virt2pml4Idx(virt), virt2pdpIdx(virt), virt2pdIdx(virt))->entries[virt2ptIdx(virt)]);
    if (pte->present) {
        if (!MASK_MUNMAP_DONTFREE(attrib)) 
            pmm_free_frame(pte->frame << 0xC);
        invlpg(virt);
        pte->value = 0x0;
    }
}

void x86_64_vmm_init(void)
{
    /*
    ** For the kheap consistancy we must unmap all page behind the kernel
    */
    vmm_unmap(
        ADD_PTR(&__KERNEL_VIRT_END, KCONFIG_MMU_PAGESIZE),
        (512 - virt2ptIdx(&__KERNEL_VIRT_END) - 1) * KCONFIG_MMU_PAGESIZE,
        MUNMAP_DONTFREE
    );
    /*
    ** Init the kernel allocator & the kernel VMM
    */
    vmm_init();
    /*
    ** Allocate all the kernel pml4 entries 
    */
}

/*
** VMM can't be initcall()
** The PMM is handled by a boot_initcall() and is totaly shared
*/
