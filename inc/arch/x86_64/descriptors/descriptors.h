/******************************************************************************
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _ARCH_x86_64_DESCRIPTORS_H_
# define _ARCH_x86_64_DESCRIPTORS_H_

enum x86_64_descriptors
{
    DESCRIPTORS_TSS_AVAILABLE_16        = 1,
    DESCRIPTORS_LDT                     = 2,
    DESCRIPTORS_TSS_BUSY_16             = 3,
    DESCRIPTORS_CALL_GATE_16            = 4,
    DESCRIPTORS_TASK_GATE               = 5,
    DESCRIPTORS_INTERRUPT_GATE_16       = 6,
    DESCRIPTORS_TRAP_GATE_16            = 7,
    DESCRIPTORS_TSS_AVAILABLE_32        = 9,
    DESCRIPTORS_TSS_AVAILABLE_64        = 9,
    DESCRIPTORS_TSS_BUSY_32             = 11,
    DESCRIPTORS_TSS_BUSY_64             = 11,
    DESCRIPTORS_CALL_GATE_32            = 12,
    DESCRIPTORS_CALL_GATE_64            = 12,
    DESCRIPTORS_INTERRUPT_GATE_32       = 14,
    DESCRIPTORS_INTERRUPT_GATE_64       = 14,
    DESCRIPTORS_TRAP_GATE_32            = 15,
    DESCRIPTORS_TRAP_GATE_64            = 15,
};

enum x86_64_gdt_selectors
{
    NULL_SELECTOR = 0x0,
    KERNEL_CODE_SELECTOR = 0x8,
    KERNEL_DATA_SELECTOR = 0x10,
    USER_CODE_SELECTOR = 0x18,
    USER_DATA_SELECTOR = 0x20,
    TSS_SELECTOR = 0x28,
};

enum x86_64_dpl
{
    DPL_LEVEL_KERNEL = 0x0,
    DPL_LEVEL_1      = 0x1,
    DPL_LEVEL_2      = 0x2,
    DPL_LEVEL_USER   = 0x3,
};

typedef enum x86_64_dpl x86_64_dpl_t;

#endif /* _ARCH_x86_64_DESCRIPTORS_H_ */
