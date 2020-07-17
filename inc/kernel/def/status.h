/********************************************************************************
** 
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _STATUS_H_
# define _STATUS_H_

/*
** Cosmos kernel status
*/
enum status {
    OK = 0,

    ERR_FATAL,
};

typedef enum status status_t;

#endif /* _STATUS_H_ */
