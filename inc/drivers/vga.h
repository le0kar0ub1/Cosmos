/******************************************************************************
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _DRIVER_VGA_H_
# define _DRIVER_VGA_H_

# include <cosmos.h>

# define VGA_WIDTH  80
# define VGA_HEIGHT 25

struct vga
{
    u16_t  attrib; // AKA the color & text
    u16_t *buff;   // located at physical address 0xB8000
    u32_t  posx;   // current pos in vga buffer x
    u32_t  posy;   // current pos in vga buffer y
};

enum vga_color
{
    VGA_BLACK       = 0x0,
    VGA_BLUE        = 0x1,
    VGA_GREEN       = 0x2,
    VGA_CYAN        = 0x3,
    VGA_RED         = 0x4,
    VGA_PINK        = 0x5,
    VGA_BROWN       = 0x6,
    VGA_LIGHT_GREY  = 0x7,
    VGA_DARK_GREY   = 0x8,
    VGA_LIGHT_BLUE  = 0x9,
    VGA_LIGHT_GREEN = 0xA,
    VGA_LIGHT_CYAN  = 0xB,
    VGA_LIGHT_RED   = 0xC,
    VGA_LIGHT_PINK  = 0xD,
    VGA_YELLOW      = 0xE,
    VGA_WHITE       = 0xF
};

void vga_printf(char const *fmt, ...);
void vga_vprintf(char const *fmt, __builtin_va_list ap);

void vga_set_color(enum vga_color bg, enum vga_color fg);
void vga_clear(void);

void vga_szputs(char const *s, size_t sz);
void vga_puts(char const *s);

void vga_cursor_enable(uint8, uint8);
void vga_cursor_disable(void);
uint16 vga_cursor_get_position(void);

#endif /* !_DRIVER_VGA_H_ */