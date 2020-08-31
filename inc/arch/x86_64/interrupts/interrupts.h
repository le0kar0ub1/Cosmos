/******************************************************************************
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _ARCH_x86_64_INTERRUPTS_H_
# define _ARCH_x86_64_INTERRUPTS_H_

# include <kernel/def/def.h>

enum interruptsNumber
{
    INT_DIVISION_BY_ZERO    = 0x0,
    INT_DEBUG               = 0x1,
    INT_NON_MASKABLE_INT    = 0x2,
    INT_BREAKPOINT          = 0x3,
    INT_OVERFLOW            = 0x4,
    INT_OUT_OF_BOUNDS       = 0x5,
    INT_INVALID_OPCODE      = 0x6,
    INT_DEVICE_NA           = 0x7,
    INT_DOUBLE_FAULT        = 0x8,
    INT_COCPU_SEG_OVERRUN   = 0x9,
    INT_INVALID_TSS         = 0xA,
    INT_SEGMENT_NOT_PRESENT = 0xB,
    INT_STACK_FAULT         = 0xC,
    INT_GP_FAULT            = 0xD,
    INT_PAGE_FAULT          = 0xE,
    INT_UNKNOW_INT          = 0xF, 
    INT_FPU_FAULT           = 0x10,
    INT_ALIGNMENT_CHECK     = 0x11,
    INT_MACHINE_CHECK       = 0x12,
    INT_SIMD                = 0x13,
    INT_VIRT_EXECPTION      = 0x14,
    /* reserved */
    INT_SECURITY_EXECPTION  = 0x1E,
    /* reserved */
    INT_IRQ0                = 0x20,
    INT_IRQ1                = 0x21,
    INT_IRQ2                = 0x22,
    INT_IRQ3                = 0x23,
    INT_IRQ4                = 0x24,
    INT_IRQ5                = 0x25,
    INT_IRQ6                = 0x26,
    INT_IRQ7                = 0x27,
    INT_IRQ8                = 0x28,
    INT_IRQ9                = 0x29,
    INT_IRQ10               = 0x2A,
    INT_IRQ11               = 0x2B,
    INT_IRQ12               = 0x2C,
    INT_IRQ13               = 0x2D,
    INT_IRQ14               = 0x2E,
    INT_IRQ15               = 0x2F,
    /* reserved */
    INT_APIC_TIMER          = 0x32,
    INT_APIC_ERROR          = 0x33,

    /*
    ** Kernel interrupt debug handler
    */
    INT_HANDMADE_DEBUG      = 0x40,
    INT_SYSCALL             = 0x80,

    INT_APIC_SPURIOUS       = 0xFF,

    MAX_INT                 = 0x100,
};

struct interrupt_frame
{
    uintptr_t gs;
    uintptr_t fs;
    uintptr_t es;
    uintptr_t ds;

    uintptr_t r15;
    uintptr_t r14;
    uintptr_t r13;
    uintptr_t r12;
    uintptr_t r11;
    uintptr_t r10;
    uintptr_t r9;
    uintptr_t r8;

    uintptr_t rax;
    uintptr_t rcx;
    uintptr_t rdx;
    uintptr_t rbx;
    uintptr_t rsi;
    uintptr_t rdi;
    uintptr_t rbp;

    uintptr_t int_num;
    uintptr_t err_code;

    uintptr_t rip;
    uintptr_t cs;
    uintptr_t rflags;
    uintptr_t rsp;
    uintptr_t ss;
};

void interrupt_dispatch(struct interrupt_frame *);

void interrupt_register_handler(uint, void (*)(struct interrupt_frame *));
void interrupt_unregister_handler(uint);
void *interrupt_get_handler_from_index(uint);

void exceptions_handler(struct interrupt_frame *);

void handmade_debug(struct interrupt_frame *);

#endif /* !_ARCH_x86_64_INTERRUPTS_H_ */
