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

/*
** Entire X86_64 IDT
*/
__aligned(16)
static struct x86_64_idt idt = {0};

/*
** Fat idt ptr
*/
__aligned(16)
static struct x86_64_idt_ptr idtptr = {
    .size   = (16 * 256) - 1,
    .offset = &idt,
};

/*
** Fill in all gates with the ISR handler & setup types
*/
void idt_init(void)
{
    extern uintptr_t x86_64_interrupt_handler;
    for (u32_t i = 0; i < 256; i++) {
        idt.gates[i].offset_1 = (u16_t)(x86_64_interrupt_handler >> 00ul);
        idt.gates[i].offset_2 = (u16_t)(x86_64_interrupt_handler >> 16ul);
        idt.gates[i].offset_3 = (u32_t)(x86_64_interrupt_handler >> 32ul);

        idt.gates[i].GateType = DESCRIPTORS_INTERRUPT_GATE_64;
        idt.gates[i].DPL      = DPL_LEVEL_KERNEL;
        idt.gates[i].Present  = 0x1;
    }

    asm volatile(
        "lidt (%%eax)"
        :
        : "a"(&idtptr)
        :
    );
}