/******************************************************************************
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include <cosmos.h>
# include <arch/x86_64/system/gdt.h>

/*
** Entire x86_64 gdt
*/
__aligned(16)
struct x86_64_gdt_segment_descriptor gdt[] = {
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
                .accessed        = false,
                .readable        = true,
                .conforming      = false,
                ._reserved0      = 1,
                ._reserved1      = 1,
                .dpl             = DPL_LEVEL_KERNEL,
                .present         = true,
                .limit_high      = 0b1111,
                .avl             = false,
                .long_mode       = 1,
                .default_op_size = 0,
                .granularity     = 1,
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
                .accessed        = false,
                .writable        = true,
                .direction       = false,
                ._reserved0      = 0,
                ._reserved1      = 1,
                .dpl             = DPL_LEVEL_KERNEL,
                .present         = true,
                .limit_high      = 0b1111,
                .avl             = false,
                .long_mode       = 1,
                .big             = 0,
                .granularity     = 1,
            .base_high = 0x0
        }
    },
    /*
    ** Kernel code selector
    */
    {
        .code = {
            .limit_low = 0xFFFF,
            .base_low = 0x0,
            .base_mid = 0x0,
                .accessed        = false,
                .readable        = true,
                .conforming      = false,
                ._reserved0      = 1,
                ._reserved1      = 1,
                .dpl             = DPL_LEVEL_USER,
                .present         = true,
                .limit_high      = 0b1111,
                .avl             = false,
                .long_mode       = 1,
                .default_op_size = 0,
                .granularity     = 1,
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
                .accessed        = false,
                .writable        = true,
                .direction       = false,
                ._reserved0      = 0,
                ._reserved1      = 1,
                .dpl             = DPL_LEVEL_USER,
                .present         = true,
                .limit_high      = 0b1111,
                .avl             = false,
                .long_mode       = 1,
                .big             = 0,
                .granularity     = 1,
            .base_high = 0x0
        }
    },
    /*
    ** One TSS, at time only one cpu is running
    */
    {
        .system = {
            .limit_low = 0xFFFF,
            .base_low = 0x0,
            .base_mid = 0x0,
                .type            = DESCRIPTORS_TSS_AVAILABLE_64,
                ._reserved0      = 0,
                .dpl             = DPL_LEVEL_USER,
                .present         = true,
                .limit_high      = 0b1111,
                ._reserved1      = 0,
                .granularity     = 1,
            .base_high = 0x0
        }
    }
};

/*
** Fat gdt ptr
*/
__aligned(16)
struct x86_64_gdt_ptr const gdtptr = {
    .size   = sizeof(gdt) - 1,
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