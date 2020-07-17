/********************************************************************************
** 
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _BOOT_H_
# define _BOOT_H_

# define __KERNEL_ADDR_TRNS 0xFFFFFFFF80000000
# define __KERNEL_VIRT_LINK 0xFFFFFFFF80100000
# define __KERNEL_PHYS_LINK 0x0000000000100000

# define P2V(x) (x + &__KERNEL_ADDR_TRNS)
# define V2P(x) (x - __KERNEL_ADDR_TRNS)

# define NULL_SELECTOR          0x00
# define KERNEL_CODE_SELECTOR   0x08
# define KERNEL_DATA_SELECTOR   0x10
# define USER_CODE_SELECTOR     0x18
# define USER_DATA_SELECTOR     0x20
# define TSS_SELECTOR           0x28

# define MMU_PRESENT   (1 << 0)
# define MMU_WRITABLE  (1 << 1)
# define MMU_SZ_TWO_MB (1 << 7)

# define PAGE_ENTRY_SZ  0x8
# define PAGE_ENTRY_NBR 0x200
# define PAGE_TOTAL_SZ  PAGE_ENTRY_NBR * PAGE_ENTRY_SZ

# define __RECURSIVE_MAPPING_ADDR 0xffffff7fbfdfe000
# define __RECURSIVE_MAPPING_IDX  510

# define KERNEL_PML4_INDEX_START ((__KERNEL_ADDR_TRNS >> 39) & ((1 << 9) - 1))
# define KERNEL_PDP_INDEX_START  ((__KERNEL_ADDR_TRNS >> 30) & ((1 << 9) - 1))
# define KERNEL_PD_INDEX_START   ((__KERNEL_ADDR_TRNS >> 21) & ((1 << 9) - 1))
# define KERNEL_PT_INDEX_START   ((__KERNEL_ADDR_TRNS >> 12) & ((1 << 9) - 1))

#endif /* _BOOT_H_ */
