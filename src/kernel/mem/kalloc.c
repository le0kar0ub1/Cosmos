/********************************************************************************
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include <kernel/mem/kalloc.h>
# include <arch/x86_64/spinlock.h>
# include <drivers/uart16650.h>
# include <lib/string.h>

static spinlock_t lock = SPINLOCK_UNLOCKED();

# define KHEAP_START ALIGN_PAGE((uintptr)(&__KERNEL_VIRT_END))
# define KHEAP_DEFAULT_ALIGNEMENT sizeof(uintptr_t)

/*
** An allocator control block
** handle the size and the usage state with the sign.
** Because we want a 64 bits aligned structure, we are using a long instead of int.
*/
typedef struct heapblock
{
    struct heapblock *back;
    long attrib;
} __packed block_t;

static_assert(sizeof(block_t) % KHEAP_DEFAULT_ALIGNEMENT == 0);

/*
** kheap start address
*/
static virtaddr_t kheap_start        = 0x0;
/*
** kheap end in-use control block
*/
static virtaddr_t kheap_end          = 0x0;
/*
** total of allocating page for the kheap
*/
static size_t     kheap_mapped_size  = 0x0;

/*
** dump the kernel heap
*/
void kalloc_dump(void)
{
    block_t *block = (block_t *)kheap_start;

    KDEBUG_QEMU_PRINTF("[Heap dump]\n");
    while ((uintptr_t)block <= (uintptr_t)kheap_end)
    {
        KDEBUG_QEMU_PRINTF(
            "    Block %s at %#X sizeof %#X\n",
            block->attrib > 0 ? "used  " : "unused",
            (uintptr_t)block,
            ABS(block->attrib)
        );
        block = ADD_PTR(block, sizeof(block_t) + ABS(block->attrib));
    }
}

/*
** map new memory pages
*/
static status_t extend_heap(size_t size)
{
    if (vmm_mmap(
        ADD_PTR(kheap_start, kheap_mapped_size),
        ALIGN_PAGE(size),
        MMAP_WRITE
    ) == NULL)
        return (ERR_VMM_FATAL);
    kheap_mapped_size += ALIGN_PAGE(size);
    return (OK);
}

/*
** is there a well sized/aligned free block
*/
static block_t *is_a_block_free(size_t size, size_t alignement)
{
    block_t *block = (block_t *)kheap_start;

    while ((uintptr_t)block <= (uintptr_t)kheap_end)
    {
        if (block->attrib < 0 && ABS(block->attrib) >= size
        && IS_ALIGNED(block, alignement)) {
           block->attrib *= -1;
           return (block);     
        }
        block = ADD_PTR(block, sizeof(block_t) + ABS(block->attrib));
    }
    return (NULL);
}

/*
** allocate a new block
*/
static block_t *allocate_new_block(size_t size, size_t alignement)
{
    block_t *oldblk = (block_t *)kheap_end;
    block_t *newblk = ADD_PTR(
            kheap_end,
            sizeof(block_t) + ABS(((block_t*)kheap_end)->attrib)
        );
    if (!IS_ALIGNED(ADD_PTR(newblk, sizeof(block_t)), alignement)) {
	    newblk = (block_t *)SUB_PTR(ALIGN(ADD_PTR(newblk, sizeof(block_t)), alignement), sizeof(block_t));
	    oldblk->attrib = oldblk->attrib > 0 ?
	        +(long)SUB_PTR(newblk, oldblk) - sizeof(block_t):
	        -(long)SUB_PTR(newblk, oldblk) - sizeof(block_t); 
    }
    if ((uintptr_t)ADD_PTR(newblk, size + sizeof(block_t)) > (uintptr_t)ADD_PTR(kheap_start, kheap_mapped_size))
	    if (extend_heap((size_t)SUB_PTR(ADD_PTR(newblk, size + sizeof(block_t)), kheap_start)) != OK)
		    return (NULL);
    newblk->attrib = size;
    newblk->back   = oldblk;
    kheap_end = (virtaddr_t)newblk;
    return (newblk);
}

/*
** real kalloc which take the size and the alignement
*/
static virtaddr_t _kalloc(size_t size, size_t alignement)
{
    block_t *block;

    if (!size)
        return (NULL);
    size = ALIGN(size, KHEAP_DEFAULT_ALIGNEMENT);
    block = is_a_block_free(size, alignement);
    if (block)
        return ((virtaddr_t)ADD_PTR(block, sizeof(block_t)));
    block = allocate_new_block(size, alignement);
    if (block)
        return ((virtaddr_t)ADD_PTR(block, sizeof(block_t)));
    return (NULL);
}

/*
** alloc aligned on the system pointer size 
*/
virtaddr_t kalloc(size_t size)
{
    return (_kalloc(size, KHEAP_DEFAULT_ALIGNEMENT));
}

/*
** alloc aligned on the given alignement
*/
virtaddr_t kalloc_aligned(size_t size, size_t alignement)
{
    if (!IS_ALIGNED(size, KHEAP_DEFAULT_ALIGNEMENT))
        return (NULL);
    return (_kalloc(size, alignement));
}

/*
** map the first page
** init global variables
** create the first control block
*/
void kalloc_init(void)
{
    vmm_mmap(
        kheap_start,
        KCONFIG_MMU_PAGESIZE,
        MMAP_WRITE
    );
    kheap_mapped_size = KCONFIG_MMU_PAGESIZE;
    kheap_start       = (virtaddr_t)KHEAP_START;
    kheap_end         = (virtaddr_t)KHEAP_START;
    ((block_t *)kheap_start)->back   = NULL;
    ((block_t *)kheap_start)->attrib = -1 * (KCONFIG_MMU_PAGESIZE - (sizeof(block_t) * 2));
}

/*
** Can't be a initcall()
** unavailable before the VMM initialization 
*/
