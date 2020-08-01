/********************************************************************************
** 
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

.code64

# include <arch/x86_64/boot/boot.h>

.section .text

.align 16
.global x86_64_isr
.type x86_64_isr, @function
x86_64_isr:
.set i, 0
.rept 256
    .align 16
    .if (i == 8 || (i >= 10 && i <= 14) || i == 17)
        nop
        nop
        .byte 0x68      // `push imm` opcode
        .byte i
        .byte 0
        .byte 0
        .byte 0
        jmp x86_64_interrupt_wrp_common
    .else
        pushq $0        // Fake error code
        .byte 0x68      // `push imm` opcode
        .byte i
        .byte 0
        .byte 0
        .byte 0
        jmp x86_64_interrupt_wrp_common
    .endif
    .set i, i + 1
.endr

/*
** Prepare dispatcher
*/
.extern interrupt_dispatch

.global x86_64_interrupt_wrp_common
.type x86_64_interrupt_wrp_common, @function
x86_64_interrupt_wrp_common:
    pushq %rbp
    pushq %rdi
    pushq %rsi
    pushq %rbx
    pushq %rdx
    pushq %rcx
    pushq %rax

    pushq %r8
    pushq %r9
    pushq %r10
    pushq %r11
    pushq %r12
    pushq %r13
    pushq %r14
    pushq %r15

    mov %ds, %rax
    pushq %rax
    mov %es, %rax
    pushq %rax
    mov %fs, %rax
    pushq %rax
    mov %gs, %rax
    pushq %rax

    movw $KERNEL_DATA_SELECTOR, %ax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs

    mov %rsp, %rdi

    call interrupt_dispatch

    popq %rax
    mov %ax, %gs
    popq %rax
    mov %ax, %fs
    popq %rax
    mov %ax, %es
    popq %rax
    mov %ax, %ds

    popq %r15
    popq %r14
    popq %r13
    popq %r12
    popq %r11
    popq %r10
    popq %r9
    popq %r8

    popq %rax
    popq %rcx
    popq %rdx
    popq %rbx
    popq %rsi
    popq %rdi
    popq %rbp

    addq $0x10, %rsp

    iretq
