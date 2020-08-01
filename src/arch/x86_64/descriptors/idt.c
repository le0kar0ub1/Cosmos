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

extern void x86_64_isr(void);

/*
** Entire x86_64 IDT
*/
__aligned(16)
struct x86_64_idt_gate idt[MAX_INT] = {
     {
         0,
         KERNEL_CODE_SELECTOR,
         0,
         0,
            DESCRIPTORS_INTERRUPT_GATE_64,
            0,
            DPL_LEVEL_KERNEL,
            true,
         0,
         0,
         0
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

/*
** Fill in all gates with the ISR handler & setup types
** load the idtptr
*/
void idt_init(void)
{
    for (u32_t i = 0; i < MAX_INT; i++)
    {
        idt[i].offset_1 = (u16_t)(((uintptr_t)x86_64_isr >> 00ul) & 
            ((1ul << 16ul) - 1ul));        
        idt[i].offset_2 = (u16_t)(((uintptr_t)x86_64_isr >> 16ul) &
            ((1ul << 16ul) - 1ul));
        idt[i].offset_3 = (u32_t)(((uintptr_t)x86_64_isr >> 32ul) &
            ((1ul << 32ul) - 1ul));
    }
    asm volatile (
        "lidt idtptr"
    );
}