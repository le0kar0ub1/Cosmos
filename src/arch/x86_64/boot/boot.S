/******************************************************************************\
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#include <arch/x86_64/boot/boot.h>

.code32

.section .text

.global _start
.type _start, @function
_start:
    cli
    cld
    movl V2P(bootstrap_stack_top), %esp

    pushl %ebx # phys multiboot structure

    call multioot_sanity
    call cpuid_detect
    call ia32e_detect

    // call setup_paging

    // LV2P $gdtptr_phys, %eax
    // lgdt (%eax)

    // popl %ebx
    // ljmp $KERNEL_CODE_SELECTOR, $(ia32_start - __KERNEL_ADDR_TRNS)

    /* 
    ** in case of return, deadloop
    */
    deadloop:
        hlt
        jmp deadloop

.section .bss

.global bootstrap_stack_top

.align 1024
bootstrap_stack_bot:
.fill 0x1000, 0x8, 0x0
bootstrap_stack_top: