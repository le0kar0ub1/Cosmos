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

static struct x86_64_idt idt = {0};

static struct x86_64_idt_ptr idtptr = {
    .size   = (16 * 256) - 1,
    .offset = &idt,
};

void idt_init(void)
{
    for (u32_t i = 0; i < 256; i++) {
        idt.gates[i].GateType = DESCRIPTORS_INTERRUPT_GATE_64;
        idt.gates[i].DPL = 0x0;
        idt.gates[i].Present = 0x1;
    }
}