/******************************************************************************\
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

.code32

#include <arch/x86_64/boot/boot.h>

.extern __BSS_START
.extern __BSS_END

.section .text

/*
** BSS section clear
*/
.global clear_bss
.type clear_bss, @function
clear_bss:
    mov V2P($__BSS_START), %eax
    mov V2P($__BSS_END), %ebx
    .bssclear:
        movb $0x0, (%eax)
        incl %eax
        cmpl %ebx, %eax
        jne .bssclear
    ret
