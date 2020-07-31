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

# define REGISTER_IO_PORT(pname, vport)                           \
    __aligned(sizeof(void *)) __used __section(".cosmos_io_port") \
    static const struct io_port const pname = {                   \
        .name = #pname,                                           \
        .port = vport                                             \
    }

/* read port (byte) */
static inline uchar inb(const struct io_port *port, ushort offset)
{
    uchar ret;
    ushort read = port->port + offset;
    asm volatile("inb %1, %0" : "=a"(ret) : "d"(read));
    return (ret);
}

/* read port (word) */
static inline ushort inw(const struct io_port *port, ushort offset)
{
    ushort ret;
    asm volatile("inw %1, %0" : "=a"(ret) : "d"(port->port + offset));
    return (ret);
}

/* read port (double) */
static inline uint ind(const struct io_port *port, ushort offset)
{
    uint ret;
    asm volatile("inl %1, %0" : "=a"(ret) : "d"(port->port + offset));
    return (ret);
}

/* write port (byte) */
static inline void outb(const struct io_port *port, ushort offset, uchar data)
{
    ushort read = port->port + offset;
    asm volatile("outb %0, %1" :: "a"(data), "d"(read));
}

/* write port (word) */
static inline void outw(const struct io_port *port, ushort offset, ushort data)
{
    asm volatile("outw %0, %1" :: "a"(data), "d"(port->port + offset));
}

/* write port (double) */
static inline void outd(const struct io_port *port, ushort offset, uint data)
{
    asm volatile("outl %0, %1" :: "a"(data), "d"(port->port + offset));
}

#endif /* _PORT_H_ */
