/******************************************************************************
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _ASSERT_H_
# define _ASSERT_H_

# include <kernel/def/status.h>

# include <stdarg.h>
static inline void panic(char const *s, ...) {}

# define assert(expr)                                           \
    if (unlikely(!(expr))) {                                    \
            panic(                                              \
                "assert(%s) failed in file %s at line %u).\n",  \
                #expr,                                          \
                __FILE__,                                       \
                __LINE__                                        \
            );                                                  \
        }                                                       \

# define assert_isok(expr) assert((status_t)expr == OK)

#endif /* _ASSERT_H_ */
