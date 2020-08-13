/******************************************************************************
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include <cosmos.h>
# include <arch/x86_64/descriptors/gdt.h>
# include <arch/x86_64/boot/boot.h>

/*
** Entire x86_64 gdt
*/
__aligned(16)
struct x86_64_gdt_segment_descriptor gdt[6] = {
    /*
    ** NULL selector
    */
    {
        .value = 0x0
    },
    /*
    ** Kernel code selector
    */
    {
        .code = {
            .limit_low = 0xFFFF,
            .base_low = 0x0,
            .base_mid = 0x0,
            .flags = 0b1010111110011010,
            .base_high = 0x0
        }
    },
    /*
    ** Kernel data selector
    */
    {
        .data = {
            .limit_low = 0xFFFF,
            .base_low = 0x0,
            .base_mid = 0x0,
            .flags = 0b0000000010010010,
            .base_high = 0x0
        }
    },
    /*
    ** User code selector
    */
    {
        .code = {
            .limit_low = 0xFFFF,
            .base_low = 0x0,
            .base_mid = 0x0,
            .flags = 0b1100111111111010,
            .base_high = 0x0
        }
    },
    /*
    ** User data selector
    */
    {
        .data = {
            .limit_low = 0xFFFF,
            .base_low = 0x0,
            .base_mid = 0x0,
            .flags = 0b1100111111110010,
            .base_high = 0x0
        }
    }
};

static_assert(sizeof(gdt) == (6 * sizeof(struct x86_64_gdt_segment_descriptor)));

/*
** Fat gdt ptr
*/
__aligned(16)
struct x86_64_gdt_ptr const gdtptr = {
    .size   = (sizeof(struct x86_64_gdt_segment_descriptor) * 6) - 1,
    .offset = &(*gdt),
};

/*
** load the gdtptr
*/
void gdt_init(void)
{
    asm volatile (
        "lgdt gdtptr"
    );
}