/********************************************************************************
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _KSYMTAB_H_
# define _KSYMTAB_H_

# include <kernel/def/def.h>

struct symbol_t
{
    void *addr;
    const char *name;
};

#define EXPORT_SYMBOL(symbol) \
    extern typeof(symbol) symbol; \
    static const char __ksym_name_##symbol[] = #symbol; \
    static const struct symbol_t __ksymtab_##symbol \
    __attribute__((__used__, section(".ksymtab.text"))) = { (void *)&symbol, __ksym_name_##symbol }

#define symbol_get_name(x) ((typeof(&x))(__symbol_get_name(#x)))
#define symbol_get_addr(x) ((typeof(&x))(__symbol_get_addr(#x)))

char const *__symbol_get_name(void *);
void *__symbol_get_addr(const char *);

#endif /* _KSYMTAB_H_ */
