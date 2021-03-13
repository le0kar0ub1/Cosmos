/******************************************************************************\
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _KERNEL_IO_DISPLAY_H_
# define _KERNEL_IO_DISPLAY_H_

# include <cosmos.h>

void printf_uart(char const *fmt, ...);
void printf_text(char const *fmt, ...);
void vprintf_uart(char const *fmt, __builtin_va_list ap);
void vprintf_text(char const *fmt, __builtin_va_list ap);

#endif /* !_KERNEL_IO_DISPLAY_H_ */
