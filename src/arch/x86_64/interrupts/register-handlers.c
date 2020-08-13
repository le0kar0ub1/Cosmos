/******************************************************************************\
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include <arch/x86_64/interrupts/interrupts.h>

static void (*interrupt_handlers[MAX_INT])(struct interrupt_frame *) = {0};

/*
** register a particular interrupt handler
*/
void interrupt_register_handler(uint intnbr, void (*handler)(struct interrupt_frame *))
{
    if (intnbr < MAX_INT)
        interrupt_handlers[intnbr] = handler;
}

/*
** unregsiter a particular handler
*/
void interrupt_unregister_handler(uint intnbr)
{
    if (intnbr < MAX_INT)
        interrupt_handlers[intnbr] = NULL;
}

/*
** get handler from interrupt number
*/
void *interrupt_get_handler_from_index(uint intnbr)
{
    if (intnbr < MAX_INT)
        return (interrupt_handlers[intnbr]);
    return (NULL);
}