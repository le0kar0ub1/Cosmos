/******************************************************************************
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _ARCH_x86_64_SYSTEM_IDT_H_
# define _ARCH_x86_64_SYSTEM_IDT_H_

# include <kernel/def/def.h>
# include <kernel/def/access.h>
# include <kernel/def/assert.h>
# include <arch/x86_64/system/descriptors.h>

struct x86_64_idt_gate
{
    u16_t offset_1  : 16;  // offset bits 0..15
    u16_t selector  : 16;  // a code segment selector in GDT or LDT
    u8_t  ist       : 3;   // holds Interrupt Stack Table offset.
    u8_t  _zero1    : 5;
    union {
        struct {
            u8_t GateType  : 4;
            u8_t Zero      : 1;
            u8_t DPL       : 2;
            u8_t Present   : 1;
        };
        u8_t attribs : 8;
    };
    u16_t offset_2  : 16;  // offset bits 16..31
    u32_t offset_3  : 32;  // offset bits 32..63
    u32_t _zero2    : 32;
} __packed;

static_assert(sizeof(struct x86_64_idt_gate) == 16ul);

struct x86_64_idt_ptr
{
    u16_t                  size;
    struct x86_64_idt_gate *offset;
} __packed;

static_assert(sizeof(struct x86_64_idt_ptr) == 10ul);

void idt_init(void);

#endif /* !_ARCH_x86_64_SYSTEM_IDT_H_ */
