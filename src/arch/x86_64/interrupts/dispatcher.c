/******************************************************************************\
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include <arch/x86_64/interrupts/interrupts.h>

/*
** Dispatch interrupt, come from common ISR
*/
void interrupt_dispatch(struct interrupt_frame *frame)
{
    void (*handler)(struct interrupt_frame *) = interrupt_get_handler_from_index(frame->int_num);

    if (handler)
        handler(frame);
    else if (frame->int_num == INT_HANDMADE_DEBUG)
        handmade_debug(frame);
    else
        exceptions_handler(frame);
}