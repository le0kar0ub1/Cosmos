/******************************************************************************
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _LIB_STDIO_H_
# define _LIB_STDIO_H_

# include <kernel/def/def.h>

void generic_vprintf(void (*szputs)(char const *, size_t), 
char const *fmt, __builtin_va_list ap);
void generic_printf(void (*szputs)(char const *, size_t), 
char const *fmt, ...);

#endif /* !_LIB_STDIO_H_ */