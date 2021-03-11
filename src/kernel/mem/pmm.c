/********************************************************************************
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include <cosmos.h>
# include <kernel/drivers/drivers.h>
# include <kernel/mem/pmm.h>
# include <kernel/io/mem.h>
# include <arch/x86_64/spinlock.h>
# include <arch/x86_64/boot/multiboot2.h>
# include <lib/string.h>

/* 
** static memory map
** (hope) will be a pmm bootstrap 
*/
static u8_t bitmap[PMM_BITMAP_SIZE];

static spinlock_t lock = SPINLOCK_UNLOCKED();

/*
** is the given frame allocated ?
*/
bool pmm_is_frame_allocated(physaddr_t frame)
{
    assert(IS_PAGE_ALIGNED(frame));
    return (bitmap[PMM_BITMAP_ADDR2IDX(frame)] & PMM_BITMAP_ADDR2MASK(frame));
}

/*
** mark all the frames as allocated between start & end address
*/
void pmm_mark_range_frame_as_allocated(physaddr_t start, physaddr_t end)
{
    assert(IS_PAGE_ALIGNED(start));
    assert(IS_PAGE_ALIGNED(end));
    spinlock_lock(&lock);
    while (start <= end)
    {
        bitmap[PMM_BITMAP_ADDR2IDX(start)] |= PMM_BITMAP_ADDR2MASK(start);
        start += KCONFIG_MMU_PAGESIZE;
    }
    spinlock_unlock(&lock);
}

/*
** mark all the frames as free between start & end address
*/
void pmm_mark_range_frame_as_free(physaddr_t start, physaddr_t end)
{
    assert(IS_PAGE_ALIGNED(start));
    assert(IS_PAGE_ALIGNED(end));
    spinlock_lock(&lock);
    while (start <= end)
    {
        bitmap[PMM_BITMAP_ADDR2IDX(start)] &= ~PMM_BITMAP_ADDR2MASK(start);
        start += KCONFIG_MMU_PAGESIZE;
    }
    spinlock_unlock(&lock);
}

/*
** Alloc ONE frame and return the address
*/
result_t pmm_alloc_frame(void)
{
    /*
    ** Begin the research at the address 0x10000
    ** If a block of 8 is non totaly used, then we have found
    */
    uintptr_t idx = 0x0;
    u8_t sub;
    spinlock_lock(&lock);
    while (idx < PMM_BITMAP_SIZE)
    {
        if (bitmap[idx] != 0xFF)
        {
            sub = 0x0;
            while (bitmap[idx] & 1 << sub)
                sub++;
            bitmap[idx] |= 1 << sub;
            spinlock_unlock(&lock);
            OK_PROPAGATION(((idx * 8) + sub) * KCONFIG_MMU_PAGESIZE);
        }
        idx++;
    }
    spinlock_unlock(&lock);
    ERR_PROPAGATION(ERR_PMM_OUT_OF_MEMORY);
}

/*
** Free the given frame
*/
void pmm_free_frame(physaddr_t frame)
{
    assert(IS_PAGE_ALIGNED(frame));
    spinlock_lock(&lock);
    bitmap[PMM_BITMAP_ADDR2IDX(frame)] &= ~PMM_BITMAP_ADDR2MASK(frame);
    spinlock_unlock(&lock);
}

extern uintptr_t __KERNEL_PHYS_END;
extern uintptr_t __KERNEL_PHYS_LINK;
extern uintptr_t __cosmos_io_mem_start;
extern uintptr_t __cosmos_io_mem_end;

static void pmm_probe(void)
{
    struct multiboot_mmap_entry const *mmap;

    /*
    ** Mark all as reserved by default
    */
    memset(bitmap, 0xFF, PMM_BITMAP_SIZE);
    /* 
    ** This is the multiboot mmap provided information
    ** Here we are freeing the un-reserved segments
    */
    mmap = multiboot.mmap_start;
    while (mmap < multiboot.mmap_end) {
        if (mmap->type == MULTIBOOT_MEMORY_AVAILABLE) {
            pmm_mark_range_frame_as_free(
                ROUND_DOWN(mmap->addr, KCONFIG_MMU_PAGESIZE),
                ALIGN(mmap->addr + mmap->len, KCONFIG_MMU_PAGESIZE)
            );
        }
        mmap = (struct multiboot_mmap_entry const *)((uintptr_t)mmap + multiboot.mmap_entry_size);
    }

    /*
    ** We will mark it as reserved and all between 0x0000000 and 0x000FFFFF
    ** just to ensure that the BIOS memory area is preserved
    */
    pmm_mark_range_frame_as_allocated(
        0x0u,
        0x100000u
    );
    assert(pmm_is_frame_allocated(0xA0000));

    /*
    ** All system registered memory area must be marked as allocated
    */
    struct memory_area *area = (struct memory_area *)&__cosmos_io_mem_start;
    while ((uintptr_t)area <= __cosmos_io_mem_end)
    {
        pmm_mark_range_frame_as_allocated(
            ROUND_DOWN(area->start, KCONFIG_MMU_PAGESIZE),
            ALIGN(area->end, KCONFIG_MMU_PAGESIZE)
        );
        area++;
    }

    /*
    ** Legitimately our kernel is in an available memory segment
    ** We must mark it as allocated
    */
    physaddr_t start = ROUND_DOWN(&__KERNEL_PHYS_LINK, KCONFIG_MMU_PAGESIZE);
    physaddr_t end   = ALIGN(&__KERNEL_PHYS_END, KCONFIG_MMU_PAGESIZE); 
    pmm_mark_range_frame_as_allocated(start, end);

    assert(pmm_is_frame_allocated(ROUND_DOWN(V2P(pmm_probe), KCONFIG_MMU_PAGESIZE)));
}

static void pmm_remove(void) {}

REGISTER_DRIVER(
    pmm,
    "PMM driver",
    COSMOS_HOOK_BOOT,
    pmm_probe,
    pmm_remove,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
)