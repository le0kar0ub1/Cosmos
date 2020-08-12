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

# include <kernel/def/def.h>
# include <drivers/vga.h>

void xklog(char const *what, enum vga_color color, char const *fmt, ...);

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

#endif /* _LIB_KRN_H_ */s