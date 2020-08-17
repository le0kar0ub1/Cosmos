/******************************************************************************\
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include <arch/x86_64/boot/boot.h>

.code32

.section .text

.global _start
.type _start, @function
_start:
    /*
    ** Clear interrupt & direction flag
    */
    cli
    cld
    /*
    ** physical stack loading
    */
    mov $V2P(bootstrap_stack_top), %esp

    pushl %ebx # phys multiboot structure

    /*
    ** Some sanity checks,
    ** All theses features are required
    */
    call multiboot_sanity
    call cpuid_detect
    call ia32e_detect

    /*
    ** clear the bss
    */
    call clear_bss

    /*
    ** Bootstrap paging setup
    */
    call setup_paging

    /*
    ** Load gdt ptr
    */
    mov $V2P(gdtptr_phys), %eax
    lgdt (%eax)

    popl %ebx
    /*
    ** Update code selector
    */
    ljmp $KERNEL_CODE_SELECTOR, $(ia32_start - __KERNEL_ADDR_TRNS)

    /* 
    ** in case of return, deadloop
    */
    .deadloop:
        hlt
        jmp .deadloop

.section .bss

.global bootstrap_stack_top

.align 1024
bootstrap_stack_bot:
.fill 0x1000, 0x8, 0x0
bootstrap_stack_top:

.section .rodata

.align 16
.global gdtptr_phys
gdtptr_phys:
    .2byte 24 - 1
    .4byte gdt - __KERNEL_ADDR_TRNS
