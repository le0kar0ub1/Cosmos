/********************************************************************************
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

.code32

.section .text

.global boot_ap
.type boot_ap, @function
boot_ap:
    cli
    cld

    
