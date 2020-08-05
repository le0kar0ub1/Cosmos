/********************************************************************************
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _KERNEL_MEM_PMM_H_
# define _KERNEL_MEM_PMM_H_

# include <kernel/mem/memory.h>

#if __UINTPTR_MAX__ == __UINT64_MAX__
    # define PMM_TOTAL_FRAME ((1ul << 40ul) / KCONFIG_MMU_PAGESIZE)
#else
    # define PMM_TOTAL_FRAME (UINTPTR_MAX / KCONFIG_MMU_PAGESIZE)
#endif

# define PMM_BITMAP_SIZE (PMM_TOTAL_FRAME / 8)

# define PMM_FRAME_ADDR_SHIFT 0xC

# define PMM_BITMAP_ADDR2IDX(x)  ((x >> PMM_FRAME_ADDR_SHIFT) / 8)
# define PMM_BITMAP_ADDR2MASK(x) (1 << (((x) >> PMM_FRAME_ADDR_SHIFT) % 8))

bool pmm_is_frame_allocated(physaddr_t frame);
void pmm_mark_range_frame_as_allocated(physaddr_t srt, physaddr_t end);
void pmm_mark_range_frame_as_free(physaddr_t srt, physaddr_t end);
physaddr_t pmm_alloc_frame(void);
void pmm_free_frame(physaddr_t frame);

#endif /* _KERNEL_MEM_PMM_H_ */
