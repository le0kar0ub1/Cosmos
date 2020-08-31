/******************************************************************************
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _KERNEL_DEF_ASSERT_H_
# define _KERNEL_DEF_ASSERT_H_

# include <cosmos.h>

# define static_assert(expr)                             \
    _Static_assert(                                      \
        expr,                                            \
        "assert(" #expr ") failed (file: " __FILE__ ")"  \
    )

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

#endif /* !_KERNEL_DEF_ASSERT_H_ */
