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

/*
** Sanity checks
*/

.extern boot_crash
.extern boot_vgaputs

/*
** multiboot checkup
*/
.global sanity_multiboot
.type sanity_multiboot, @function
sanity_multiboot:
    mov V2P(_err_multiboot), %esi
    cmp $0x36d76289, %eax
    jne boot_crash
    ret


/*
** detect the cpuid
** Is a fatal feature
*/
.global cpuid_detect
.type cpuid_detect, @function
cpuid_detect:
    pushf
    pop %eax
    mov %eax, %ecx

    xor $(1 << 21), %eax
    push %eax
    popf
    pushf
    pop %eax
    push %ecx
    popf
    cmp %ecx, %eax
    jne cpuid_detected

    mov V2P(_err_cpuid), %esi
    call boot_crash
cpuid_detected:
    ret

/*
** Check if long mode is supported
** fatal feature
*/
.global lm_ckeckup
.type lm_ckeckup, @function
lm_ckeckup:
    mov $0x80000000, %eax
    cpuid
    cmp $0x80000001, %eax
    jb noLongMode

    mov $0x80000001, %eax
    cpuid
    test $(1 << 29), %edx
    jz noLongMode
    ret
    noLongMode:
        mov V2P(_err_nolm), %esi
        call boot_crash

/*
** Early Error data
*/

.section .rodata

_err_multiboot: .asciz "Invalid multiboot"
_err_cpuid:     .asciz "CPUID not detected"
_err_nolm:      .asciz "long mode not supported"
