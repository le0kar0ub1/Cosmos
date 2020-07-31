/******************************************************************************
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include <drivers/uart16650.h>
# include <kernel/init/initcalls.h>
# include <kernel/drivers/drivers.h>

REGISTER_IO_PORT(uart16650_com1, 0x3F8);
REGISTER_IO_PORT(uart16650_com2, 0x2F8);
REGISTER_IO_PORT(uart16650_com3, 0x3E8);
REGISTER_IO_PORT(uart16650_com4, 0x2E8);

/*
** check if we can receive char from COM
*/
static uchar uart16650_received(void)
{
    return inb(&uart16650_com1, 5) & 1;
}

/*
** read a char on the COM port
*/
static uchar uart16650_read(void)
{
    while (uart16650_received() == 0);
    return inb(&uart16650_com1, 0);
}

/*
** chech if the COM is empty
*/
static uchar uart16650_is_transmit_empty(void)
{
    return inb(&uart16650_com1, 5) & 0x20;
}

/*
** write the given char on the COM port
*/
static void write_uart16650(char val)
{
    while (uart16650_is_transmit_empty() == 0);
    outb(&uart16650_com1, 0, val);
}

// static spinlock_t lock = SPINLOCK_INIT();

// /*
// ** the printf callable function 
// */
// void uart16650_szputs(char const *s, size_t sz)
// {
//     spinlock_lock(&lock);
//     for (u32_t i = 0x0; s[i] && i < sz; i++)
//         write_uart16650(s[i]);
//     spinlock_unlock(&lock);
// }

/*
** Must Not Be Used
*/
void uart16650_puts(char const *s)
{
    for (u32_t i = 0x0; s[i]; i++)
        write_uart16650(s[i]);
}

/*
** UART16650 init sequence
*/
static void uart16650_init(void)
{
    outb(&uart16650_com1, 0x1, 0x00);  // Disable all interrupts
    outb(&uart16650_com1, 0x3, 0x80);  // Enable DLAB (set baud rate divisor)
    outb(&uart16650_com1, 0x0, 0x03);  // Set divisor to 3 (lo byte) 38400 baud
    outb(&uart16650_com1, 0x1, 0x00);  // (hi byte)
    outb(&uart16650_com1, 0x3, 0x03);  // 8 bits, no parity, one stop bit
    outb(&uart16650_com1, 0x2, 0xC7);  // Enable FIFO, clear them, with 14-byte threshold
    outb(&uart16650_com1, 0x4, 0x0B);  // IRQs enabled, RTS/DSR set
}

REGISTER_BOOT_INITCALL(uart16650_init);

REGISTER_DRIVER(
    "uart16650",
    uart16650_init,
    NULL,
    NULL,
    NULL
);