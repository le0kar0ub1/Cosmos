/********************************************************************************
** 
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _ACCESS_H_
# define _ACCESS_H_

enum access_flag {
    R = 4,
    W = 2,
    X = 1,
    RW = 6,
    RX = 5,
    RWX = 7,
};

typedef enum access_flag access_flag_t;

# define IS_READABLE(x)   (x & 4)
# define IS_WRITABLE(x)   (x & 2)
# define IS_EXECUTABLE(x) (x & 1)

#endif /* _ACCESS_H_ */
