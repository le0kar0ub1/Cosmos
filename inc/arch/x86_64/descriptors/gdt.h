/******************************************************************************
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _ARCH_x86_64_GDT_H_
# define _ARCH_x86_64_GDT_H_

# include <kernel/def/def.h>
# include <kernel/def/access.h>
# include <kernel/def/assert.h>
# include <arch/x86_64/descriptors/descriptors.h>

struct x86_64_gdt_code_segment_descriptor
{
    u16_t limit_low: 16;
    u16_t base_low: 16;
    u8_t base_mid: 8;
    union {
        struct {
            u8_t accessed: 1;
            u8_t readable: 1;
            u8_t conforming: 1;
            u8_t _reserved0: 1;
            u8_t _reserved1: 1;
            u8_t dpl: 2;
            u8_t present: 1;
            u8_t limit_high: 4;
            u8_t avl: 1;
            u8_t long_mode: 1;
            u8_t default_op_size: 1;
            u8_t granularity: 1;
        };
        u16_t flags: 16;
    };
    u8_t base_high: 8;
} __packed;

static_assert(sizeof(struct x86_64_gdt_code_segment_descriptor) == 8ul);

struct x86_64_gdt_data_segment_descriptor
{
    u16_t limit_low: 16;
    u16_t base_low: 16;
    u8_t base_mid: 8;
    union {
        struct {
            u8_t accessed: 1;
            u8_t writable: 1;
            u8_t direction: 1;
            u8_t _reserved0: 1;
            u8_t _reserved1: 1;
            u8_t dpl: 2;
            u8_t present: 1;
            u8_t limit_high: 4;
            u8_t avl: 1;
            u8_t long_mode: 1;
            u8_t big: 1;
            u8_t granularity: 1;
        };
        u16_t flags: 16;
    };
    u8_t base_high: 8;
} __packed;

static_assert(sizeof(struct x86_64_gdt_data_segment_descriptor) == 8ul);

struct x86_64_gdt_system_segment_descriptor
{
    u16_t limit_low: 16;
    u16_t base_low: 16;
    u8_t base_mid: 8;
    union {
        struct {
            u8_t type: 4;
            u8_t _reserved0: 1;
            u8_t dpl: 2;
            u8_t present: 1;
            u8_t limit_high: 4;
            u8_t _reserved1: 3;
            u8_t granularity: 1;
        };
        u16_t flags: 16;
    };
    u8_t base_high: 8;
} __packed;

static_assert(sizeof(struct x86_64_gdt_system_segment_descriptor) == 8ul);

/*
** Stolen well done encapsulation for segment manipulation
*/
struct x86_64_gdt_segment_descriptor
{
    union {
        struct x86_64_gdt_code_segment_descriptor code;
        struct x86_64_gdt_data_segment_descriptor data;
        struct x86_64_gdt_system_segment_descriptor system;
        uint64 value: 64;
    };
};

static_assert(sizeof(struct x86_64_gdt_segment_descriptor) == 8);

struct x86_64_gdt_ptr
{
    u16_t                                size;
    struct x86_64_gdt_segment_descriptor *offset;
} __packed;

static_assert(sizeof(struct x86_64_gdt_ptr) == 10ul);

void gdt_init(void);

#endif /* !_ARCH_x86_64_GDT_H_ */
