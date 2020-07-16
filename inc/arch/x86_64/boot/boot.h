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

// # define P2V(x) (x + &__KERNEL_ADDR_TRNS)
# define V2P(x) (x - __KERNEL_ADDR_TRNS)

#endif /* _BOOT_H_ */
