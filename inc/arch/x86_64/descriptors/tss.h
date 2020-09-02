/******************************************************************************
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _ARCH_x86_64_TSS_H_
# define _ARCH_x86_64_TSS_H_

# include <kernel/def/def.h>
# include <kernel/def/access.h>
# include <kernel/def/assert.h>
# include <arch/x86_64/descriptors/descriptors.h>

struct x86_64_tss
{
    u32_t _reserved0;
    u64_t rsp0;
    u64_t rsp1;
    u64_t rsp2;
    u64_t _reserved1;
    u64_t ist1;
    u64_t ist2;
    u64_t ist3;
    u64_t ist4;
    u64_t ist5;
    u64_t ist6;
    u64_t ist7;
    u64_t _reserved2;
    u16_t _reserved3;
    u16_t iopb;
} __packed;

static_assert(sizeof(struct x86_64_tss) == 0x68);

void tss_init(u32_t entries);

#endif /* !_ARCH_x86_64_TSS_H_ */
