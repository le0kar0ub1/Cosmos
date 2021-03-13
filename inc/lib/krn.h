/******************************************************************************
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _LIB_KRN_H_
# define _LIB_KRN_H_

# include <cosmos.h>
# include <kernel/def/def.h>
# include <drivers/vga.h>

/**
 * The 0x40 interrupt is mapped on a debugger
 */
#define cpudump() asm volatile("int $0x40")

void hexdump(void *area, u32_t sz);

void xklog(char const *what, enum vga_color color, char const *fmt, ...);

u8_t checksum8(u8_t *buffer, size_t size);
u16_t checksum16(u16_t *buffer, size_t size);
u32_t checksum32(u32_t *buffer, size_t size);
u64_t checksum64(u64_t *buffer, size_t size);

/*
** Kernel info
*/
# define klog(fmt, ...)             \
            xklog(                  \
                "LOG",              \
                VGA_LIGHT_BLUE,     \
                fmt,                \
                __VA_ARGS__         \  
            )

/*
** Kernel warning
*/
# define kwrn(fmt, ...)             \
            xklog(                  \
                "WRN",              \
                VGA_YELLOW,         \
                fmt,                \
                __VA_ARGS__         \  
            )

/*
** Kernel error
*/
# define kerr(fmt, ...)             \
            xklog(                  \
                "ERR",              \
                VGA_LIGHT_RED,      \
                fmt,                \
                __VA_ARGS__         \  
            )

#endif /* !_LIB_KRN_H_ */s
