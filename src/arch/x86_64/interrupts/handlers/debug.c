/******************************************************************************
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include <cosmos.h>
# include <arch/x86_64/interrupts/interrupts.h>
# include <drivers/uart16650.h>

void handmade_debug(struct interrupt_frame *frame)
{
    KDEBUG_QEMU("       \n\
        \rrax:    %#X   \n\
        \rrcx:    %#X   \n\
        \rrdx:    %#X   \n\
        \rrbx:    %#X   \n\
        \rrsi:    %#X   \n\
        \rrdi:    %#X   \n\
        \r              \n\
        \rr15:    %#X   \n\
        \rr14:    %#X   \n\
        \rr13:    %#X   \n\
        \rr12:    %#X   \n\
        \rr11:    %#X   \n\
        \rr10:    %#X   \n\
        \rr9:     %#X   \n\
        \rr8:     %#X   \n\
        \r              \n\
        \rrbp:    %#X   \n\
        \rrsp:    %#X   \n\
        \r              \n\
        \rrflags: %#B   \n\
        \r              \n\
        \rrip:    %#X   \n\
        \r              \n\
        \rcs:     %#X   \n\
        \rgs:     %#X   \n\
        \rfs:     %#X   \n\
        \res:     %#X   \n\
        \rds:     %#X   \n\
        \rss:     %#X   \n\
    ");
}