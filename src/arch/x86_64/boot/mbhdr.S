/********************************************************************************
** 
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

.code32

.section .multiboot, "awdx"

/*
** The multiboot header, the bootloader need to found it at the very beginning.
** To ensure that's the case, let's allocate a section.
*/
.balign 4
multiboot_header:
    .4byte 0xE85250D6                 # magic
    .4byte 0x0                        # architecture 0 (protected mode i386)
    .4byte multiboot_header_end - multiboot_header  # multiboot_header length

    .4byte 0x100000000 - (0xE85250D6 + 0x0 + (multiboot_header_end - multiboot_header)) # checksum

    .2byte 0x0  # type
    .2byte 0x0  # flags
    .4byte 0x8  # size
multiboot_header_end:
