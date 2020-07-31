/******************************************************************************
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _DRIVER__UART1650_H_
# define _DRIVER__UART1650_H_

# include <cosmos.h>

void uart1650_printf(char const *fmt, ...);
void uart1650_vprintf(char const *fmt, __builtin_va_list ap);

void uart1650_szputs(char const *s, size_t sz);
void uart1650_puts(char const *s);

#endif /* _DRIVER__UART1650_H_ */