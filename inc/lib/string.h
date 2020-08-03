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

void *memcpy(void *, const void *, size_t);
void *memcpyv(void *, const void *, size_t, u8_t);
bool memcmp(const void *, const void *, size_t);
void *memset(void *, int, size_t);
void *memsetw(void *x, int, size_t);
void *memsetd(void *x, int, size_t);
void *memsetq(void *x, int, size_t);

bool strcmp(char const *, char const *);
bool strncmp(char const *, char const *, size_t);
u32_t strlen(char const *);

#endif /* _LIB_STDIO_H_ */