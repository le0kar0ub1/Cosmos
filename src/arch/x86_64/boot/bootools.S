/******************************************************************************\
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

.code32

.section .text

/*
** VGA early put, used mostly for fatal errors
*/
.global boot_vgaputs
.type boot_vgaputs, @function
boot_vgaputs:
    push %edi
    push %eax
    mov $0xb8000, %edi

    .vgaputs_loop:
        movb (%esi), %al
        cmp $0x0, %al
        je .end_vgaputs
        movb $0x4F, 1(%edi)
        movb %al, (%edi)
        incl %esi
        addl $0x2, %edi
        jmp .vgaputs_loop
    .end_vgaputs:

    pop %eax
    pop %edi
    ret

.global boot_crash
.type boot_crash, @function
boot_crash:
    call boot_vgaputs
    hlt
    jmp .
