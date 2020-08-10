/********************************************************************************
** 
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _KERNEL_DEF_STATUS_H_
# define _KERNEL_DEF_STATUS_H_

/*
** Cosmos kernel status
*/
typedef enum status {
    OK = 0,

    ERR_PMM_OUT_OF_MEMORY,
    ERR_VMM_ALREADY_MAPPED,

    ERR_FATAL,
} status_t;

/*
** A bad result implementation.
*/
typedef uint64 any64_t;

typedef struct result
{
    status_t status;
    any64_t  result;
} __packed result_t;

/*
** A set of macro for a simple life
*/
# define RESULT_IS_ERR(x)       (x.status != OK)
# define RESULT_IS_OK(x)        !(STATUS_IS_ERR(x))

# define UNWRAP(res, type)           \
            (type)(res.result)

# define RAISE_IF(tgt, res, type)    \
            if (RESULT_IS_ERR(res))  \
                return (res)

# define UNWRAP_OR_RAISE(tgt, res, type)    \
            if (RESULT_IS_ERR(res))         \
                return (res);               \
            type tgt = UNWRAP(res, type);

#endif /* _KERNEL_DEF_STATUS_H_ */
