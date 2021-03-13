/******************************************************************************\
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include <cosmos.h>
# include <kernel/io/display.h>

/**
 * Wrapper for arch-UART printf
 */
void printf_uart(char const *fmt, ...)
{
    __builtin_va_list ap;
    __builtin_va_start(ap, fmt);
    cosmos_get_config()->vprintf_uart(fmt, ap);
    __builtin_va_end(ap);
}

/**
 * Wrapper for arch-UART vprintf
 */
void vprintf_uart(char const *fmt, __builtin_va_list ap)
{
    cosmos_get_config()->vprintf_uart(fmt, ap);
}


/**
 * Wrapper for arch-TEXT printf
 */
void printf_text(char const *fmt, ...)
{
    __builtin_va_list ap;
    __builtin_va_start(ap, fmt);
    cosmos_get_config()->vprintf_text(fmt, ap);
    __builtin_va_end(ap);
}

/**
 * Wrapper for arch-TEXT vprintf
 */
void vprintf_text(char const *fmt, __builtin_va_list ap)
{
    cosmos_get_config()->vprintf_text(fmt, ap);
}