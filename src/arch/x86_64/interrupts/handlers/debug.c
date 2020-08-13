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

/*
** handler use for kernel debugging
*/
void handmade_debug(struct interrupt_frame *frame)
{
    KDEBUG_QEMU_PRINTF("[DUMP CPU 0]\n\
        \rrax: %016#X   rbx: %016#X\n\
        \rrcx: %016#X   rsi: %016#X\n\
        \rrdx: %016#X   rdi: %016#X\n\
        \r\n\
        \rr15: %016#X   r11: %016#X\n\
        \rr14: %016#X   r10: %016#X\n\
        \rr13: %016#X   r9:  %016#X\n\
        \rr12: %016#X   r8:  %016#X\n\
        \r\n\
        \rrbp: %016#X\n\
        \rrsp: %016#X\n\
        \r\n\
        \rflg: %016#B\n\
        \r\n\
        \rrip: %016#X\n\
        \r\n\
        \rcs:  %04#X   es: %04#X\n\
        \rgs:  %04#X   ds: %04#X\n\
        \rfs:  %04#X   ss: %04#X\n\
    \r",
        frame->rax, frame->rbx,
        frame->rcx, frame->rsi,
        frame->rdx, frame->rdi,
        frame->r15, frame->r11,
        frame->r14, frame->r10,
        frame->r13, frame->r9,
        frame->r12, frame->r8,
        frame->rbp,
        frame->rsp,
        frame->rflags,
        frame->rip,
        frame->cs, frame->es,
        frame->gs, frame->ds,
        frame->fs, frame->ss
    );
}