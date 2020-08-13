/******************************************************************************\
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include <arch/x86_64/descriptors/idt.h>
# include <arch/x86_64/descriptors/descriptors.h>
# include <arch/x86_64/interrupts/interrupts.h>

/*
** Entire x86_64 IDT
*/
__aligned(16)
struct x86_64_idt_gate idt[MAX_INT] = {
    {
        .offset_1 = 0,
        .selector = GDT_KERNEL_CODE_SELECTOR,
        .ist      = 0,
        ._zero1   = 0,
            .GateType = DESCRIPTORS_INTERRUPT_GATE_64,
            .Zero     = 0,
            .DPL      = DPL_LEVEL_KERNEL,
            .Present  = true,
        .offset_2 = 0,
        .offset_3 = 0,
        ._zero2   = 0
    }
};

static_assert(sizeof(idt) == (MAX_INT * sizeof(struct x86_64_idt_gate)));

/*
** Fat idt ptr
*/
__aligned(16)
struct x86_64_idt_ptr const idtptr = {
    .size   = (sizeof(struct x86_64_idt_gate) * MAX_INT) - 1,
    .offset = &(*idt),
};

extern void x86_64_isr(void);

/*
** Fill in all gates with the ISR handler & setup types
** load the idtptr
*/
void idt_init(void)
{
    uintptr_t handler = (uintptr_t)x86_64_isr;
    u32_t gate = 0x0;

    while (gate < MAX_INT)
    {
        idt[gate].offset_1 = (u16_t)((handler >> 00ul) & ((1ul << 16ul) - 1ul));
        idt[gate].selector = GDT_KERNEL_CODE_SELECTOR;
            idt[gate].GateType = DESCRIPTORS_INTERRUPT_GATE_64;
            idt[gate].DPL      = DPL_LEVEL_KERNEL;
            idt[gate].Present  = true;
        idt[gate].offset_2 = (u16_t)((handler >> 16ul) & ((1ul << 16ul) - 1ul));
        idt[gate].offset_3 = (u32_t)((handler >> 32ul) & ((1ul << 32ul) - 1ul));
        handler += 0x10;
        gate += 0x1;
    }

    asm volatile (
        "lidt idtptr"
    );
}