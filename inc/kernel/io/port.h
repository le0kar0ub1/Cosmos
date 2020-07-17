/********************************************************************************
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _PORT_H_
# define _PORT_H_

# include <kernel/def/def.h>

/*
** A defined port
*/
struct io_port {
    char const *name;
    ushort port;
};

# define REGISTER_IO_PORT(name, port)       \
    static const struct io_port name = {    \
        .name = name,                       \
        .port = port,                       \
    };                                      \

#endif /* _PORT_H_ */
