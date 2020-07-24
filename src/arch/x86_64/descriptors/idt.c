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

extern uintptr_t x86_64_interrupt_handler;

/*
** Entire x86_64 IDT
*/
__aligned(16)
static struct x86_64_idt_gate idt[MAX_INT] = {0};

/*
** Fat idt ptr
*/
__aligned(16)
struct x86_64_idt_ptr const idtptr = {
    .size   = (sizeof(struct x86_64_idt_gate) * MAX_INT) - 1,
    .offset = idt,
};

/*
** Fill in all gates with the ISR handler & setup types
*/
void idt_init(void)
{
    for (u32_t i = 0; i < MAX_INT; i++) {
        idt[i].offset_1 = (u16_t)(x86_64_interrupt_handler >> 00ul);
        idt[i].offset_2 = (u16_t)(x86_64_interrupt_handler >> 16ul);
        idt[i].offset_3 = (u32_t)(x86_64_interrupt_handler >> 32ul);

        idt[i].GateType = DESCRIPTORS_INTERRUPT_GATE_64;
        idt[i].DPL      = DPL_LEVEL_KERNEL;
        idt[i].Present  = 0x1;
    }

    asm volatile (
        "lidt idtptr"
    );
}