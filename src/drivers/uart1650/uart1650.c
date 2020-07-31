/******************************************************************************
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include <drivers/uart1650.h>
# include <kernel/init/initcalls.h>
# include <kernel/drivers/drivers.h>

REGISTER_IO_PORT(uart1650_com1, 0x3f8);

/*
** check if we can receive char from COM
*/
static uchar uart1650_received(void)
{
    return inb(&uart1650_com1, 5) & 1;
}

/*
** read a char on the COM port
*/
static char read_uart1650(void)
{
    while (uart1650_received() == 0);
    return inb(&uart1650_com1, 0);
}

/*
** chech if the COM is empty
*/
static uchar is_transmit_empty(void)
{
    return inb(&uart1650_com1, 5) & 0x20;
}

/*
** write the given char on the COM port
*/
static void write_uart1650(char val)
{
    while (is_transmit_empty() == 0);
    outb(&uart1650_com1, 0, val);
}

static spinlock_t lock = SPINLOCK_INIT();

/*
** the printf callable function 
*/
void uart1650_szputs(char const *s, size_t sz)
{
    spinlock_lock(&lock);
    for (u32_t i = 0x0; s[i] && i < sz; i++)
        write_uart1650(s[i]);
    spinlock_unlock(&lock);
}

/*
** Must Not Be Used
*/
void uart1650_puts(char const *s)
{
    for (u32_t i = 0x0; s[i]; i++)
        write_uart1650(s[i]);
}

/*
** UART1650 COM init sequence
*/
static void uart1650_init(void)
{
    outb(&uart1650_com1, 0x1, 0x00);  // Disable all interrupts
    outb(&uart1650_com1, 0x3, 0x80);  // Enable DLAB (set baud rate divisor)
    outb(&uart1650_com1, 0x0, 0x03);  // Set divisor to 3 (lo byte) 38400 baud
    outb(&uart1650_com1, 0x1, 0x00);  // (hi byte)
    outb(&uart1650_com1, 0x3, 0x03);  // 8 bits, no parity, one stop bit
    outb(&uart1650_com1, 0x2, 0xC7);  // Enable FIFO, clear them, with 14-byte threshold
    outb(&uart1650_com1, 0x4, 0x0B);  // IRQs enabled, RTS/DSR set
}

REGISTER_BOOT_INITCALL(uart1650_init);


REGISTER_DRIVER(
    "uart1650",
    uart1650_init,
    NULL,
    NULL,
    NULL
);