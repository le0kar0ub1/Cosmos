/********************************************************************************
** 
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include <cosmos.h>
# include <lib/krn.h>
# include <drivers/vga.h>

# define HEXDUMP_FORMAT 0x10

static void dump_as_char(char const *area, u32_t sz)
{
    u32_t inc = 0;

    while (inc < sz)
    {
        KDEBUG_PRINTF("%c", area[inc] == 0 ? '.' : area[inc]);
        inc++;
    }
}

void hexdump(void *area, u32_t sz)
{
    u32_t inc = 0;
    u8_t *ptr = (u8_t *)area;
    u32_t diff = 0;

    while (inc < sz)
    {
        if (inc % HEXDUMP_FORMAT == 0) {
            if (inc != 0)
                dump_as_char((char const *)((uintptr_t)area + inc - HEXDUMP_FORMAT), HEXDUMP_FORMAT);
            KDEBUG_PRINTF("\n%#X: ", (uintptr_t)area + inc);
        }
        KDEBUG_PRINTF("%02x", ptr[inc]);
        if (inc % 2 == 1)
            KDEBUG_PRINTF(" ");
        inc++;
    }
    while (inc % HEXDUMP_FORMAT != 0)
    {
        KDEBUG_PRINTF("00");
        if (inc % 2 == 1)
            KDEBUG_PRINTF(" ");
        inc++;
        diff++;
    }
    dump_as_char((char const *)((uintptr_t)area + inc - HEXDUMP_FORMAT), HEXDUMP_FORMAT - diff);
    dump_as_char("................", diff);
}

# undef HEXDUMP_FORMAT