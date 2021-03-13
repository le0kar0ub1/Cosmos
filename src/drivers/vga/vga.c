/********************************************************************************
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include <drivers/vga.h>
# include <kernel/io/spinlock.h>
# include <kernel/io/mem.h>
# include <kernel/io/port.h>
# include <kernel/mem/memory.h>
# include <kernel/drivers/drivers.h>
# include <lib/string.h>

/*
** VGA buffer size below isn't correct
** in fact we declare here the size used
*/
REGISTER_IO_PMM(
    vga_buffer,
    0xB8000,
    0xB8000 + (2 * VGA_WIDTH * VGA_HEIGHT),
    RW
);

/*
** VGA handling data
*/
static struct vga hvga =
{
    .attrib = 0x0,
    .buff = (u16_t *)P2V(0xB8000),
    .posx = 0x0,
    .posy = 0x0,
};

REGISTER_IO_PORT(
    map_mask_reg,
    0x3C4
);

REGISTER_IO_PORT(
    graphic_mode_reg,
    0x3CE
);

REGISTER_IO_PORT(
    crtc_index,
    0x3D4
);

REGISTER_IO_PORT(
    crtc_data,
    0x3D5
);

/*
** enable the cursor
*/
void vga_cursor_enable(uint8 start, uint8 end)
{
    outb(&crtc_index, 0x0, 0x0A);
    outb(&crtc_data, 0x0, (inb(&crtc_data, 0x0) & 0xC0) | start);

    outb(&crtc_index, 0x0, 0x0B);
    outb(&crtc_data, 0x0, (inb(&crtc_data, 0x0) & 0xE0) | end);
}

/*
** disable the cursor
*/
void vga_cursor_disable(void)
{
    outb(&crtc_index, 0x0, 0x0A);
    outb(&crtc_data, 0x0, 0x20);
}

/*
** Synchronize the cursor with the virtual cursor
*/
static void vga_cursor_update(void)
{
    uint pos = hvga.posy * VGA_WIDTH + hvga.posx;
    outb(&crtc_index, 0x0, 14);
    outb(&crtc_data, 0x0, pos >> 8);
    outb(&crtc_index, 0x0, 15);
    outb(&crtc_data, 0x0, pos);
}

/*
** Set the screen cursor position
*/
uint16 vga_cursor_get_position(void)
{
    uint16 pos = 0x0;

    outb(&crtc_index, 0x0, 0x0F);
    pos |= inb(&crtc_data, 0x0);
    outb(&crtc_index, 0x0, 0x0E);
    pos |= ((uint16)inb(&crtc_data, 0x0)) << 0x8;
    return (pos);
}

/*
** VGA set the background & foreground color
*/
void vga_set_color(enum vga_color bg, enum vga_color fg)
{
    hvga.attrib = ((bg << 0x4) | (fg & 0xF)) << 0x8;
}

/*
** scroll one line
*/
static void vga_scroll(void)
{
    void *start = (void *)(vga_buffer.start + (VGA_WIDTH * 2));
    u32_t size = hvga.posy * VGA_WIDTH * 2;

    if(hvga.posy < VGA_HEIGHT - 0x1)
        return;
    memcpy((void *)vga_buffer.start, start, size);
    start = (void *)(vga_buffer.start + size);
    memsetw(start, hvga.attrib | 0x20, VGA_WIDTH);
}

/*
** fulle screen clear
*/
void vga_clear(void)
{
    memsetw(hvga.buff, hvga.attrib | 0x20, VGA_WIDTH * VGA_HEIGHT);
    hvga.posx = 0x0;
    hvga.posy = 0x0;
    vga_cursor_update();
}

/*
** Print a char
*/
static void vga_putchar(int c)
{
    switch (c)
    {
        case '\n': /* new line */
            hvga.posx = 0x0;
            hvga.posy++;
            break;
        case '\t': /* tabulation */
            hvga.posx = (hvga.posx + 8u) & ~7u;
            break;
        case '\r': /* carriage return */
            hvga.posx = 0;
            break;
        case '\b': /* backspace */
            if (hvga.posx == 0) {
                hvga.posy -= (hvga.posy > 0);
                hvga.posx = VGA_WIDTH - 1;
            } else {
                hvga.posx -= (hvga.posx > 0);
            }
            break;
        default:
            *(hvga.buff + hvga.posy * VGA_WIDTH + hvga.posx) = hvga.attrib | (uchar)c;
            hvga.posx += 1;
            break;
    }
    hvga.posy += (hvga.posx >= VGA_WIDTH);
    hvga.posx *= (hvga.posx < VGA_WIDTH);
    while (hvga.posy >= VGA_HEIGHT) {
        vga_scroll();
        hvga.posy -= 1;
    }
}

static spinlock_t lock = SPINLOCK_UNLOCKED();

/*
** The printf callable function
*/
void vga_szputs(char const *s, size_t sz)
{
    spinlock_lock(&lock);
    for (size_t i = 0x0; s[i] &&  i < sz; i++)
        vga_putchar(s[i]);
    vga_cursor_update();
    spinlock_unlock(&lock);
}

/*
** Must Not Be Used
*/
void vga_puts(char const *s)
{
    while (*s) {
        vga_putchar(*s);
        s++;
    }
    vga_cursor_update();
}

/*
** Clear the screen & set the color 
*/
static void vga_probe(void)
{
    vga_set_color(VGA_BLACK, VGA_WHITE);
    vga_clear();
}

static void vga_remove(void) {}

REGISTER_DRIVER(
    vga,
    "VGA driver",
    COSMOS_HOOK_BOOT,
    vga_probe,
    vga_remove,
    NULL,
    NULL,
    NULL,
    NULL,
    vga_buffer,
    NULL
);