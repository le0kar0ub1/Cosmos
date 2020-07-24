/******************************************************************************
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _ARCH_x86_64_IDT_H_
# define _ARCH_x86_64_IDT_H_

# include <kernel/def/def.h>
# include <kernel/def/access.h>
# include <kernel/def/assert.h>
# include <arch/x86_64/descriptors/descriptors.h>

struct x86_64_idt_gate
{
   uintptr_t offset_1 : 16;  // offset bits 0..15
   uintptr_t selector : 16;  // a code segment selector in GDT or LDT
   uintptr_t ist      : 3;   // holds Interrupt Stack Table offset.
   uintptr_t _zero1   : 5;
   union {
        struct {
            uintptr_t GateType  : 4;
            uintptr_t Zero      : 1;
            uintptr_t DPL       : 2;
            uintptr_t Present   : 1;
        };
        uintptr_t attribs : 8;
    };
   uintptr_t offset_2 : 16;  // offset bits 16..31
   uintptr_t offset_3 : 32;  // offset bits 32..63
   uintptr_t _zero2   : 32;
} __packed;

static_assert(sizeof(struct x86_64_idt_gate) == 16ul);

struct x86_64_idt
{
    struct x86_64_idt_gate gates[256];
} __packed;

static_assert(sizeof(struct x86_64_idt) == (16ul * 256ul));

struct x86_64_idt_ptr
{
    u16_t              size;
    struct x86_64_idt *offset;
} __packed;

static_assert(sizeof(struct x86_64_idt_ptr) == 10ul);

void idt_init(void);

#endif /* _ARCH_x86_64_IDT_H_ */
