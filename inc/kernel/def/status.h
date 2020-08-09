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
enum status {
    OK = 0,

    ERR_PMM_OUT_OF_MEMORY,
    ERR_VMM_ALREADY_MAPPED,

    ERR_FATAL,
};

typedef enum status status_t;

#endif /* _KERNEL_DEF_STATUS_H_ */
