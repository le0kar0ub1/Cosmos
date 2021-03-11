/******************************************************************************
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include <lib/stdio.h>
# include <lib/string.h>
# include <lib/stdlib.h>
# include <kernel/def/def.h>

/* Caller printer */
static void (*caller_szputs)(char const *, size_t);

/* formatter */
bool hshtag = false;
u32_t align = false;

/* Printf buffer */
#define PRINTF_BUFFER_LENGHT 0x400
static u32_t incbuf = 0x0;
static char prbuffer[PRINTF_BUFFER_LENGHT];

static void printf_dumpBuffer(void)
{
    caller_szputs(prbuffer, incbuf);
    incbuf = 0x0;
}

static void printf_handleWrite(char c)
{
    if (incbuf >= PRINTF_BUFFER_LENGHT)
        return;
    prbuffer[incbuf] = c;
    incbuf += 0x1;
}

static void printf_handleNumberBaseWrite(char c)
{
    if (c > 0x39)
        printf_handleWrite(c + 0x7);
    else
        printf_handleWrite(c);
}

static void multibase_put32(int n, u8_t base)
{
    if (n < 0) {
        printf_handleWrite('-');
        n = n * -1;
    }
    if (n >= base)
        multibase_put32(n / base, base);
    printf_handleNumberBaseWrite((n % base) + 0x30);
}

static void multibase_put64(long n, u8_t base)
{
    if (n < 0) {
        printf_handleWrite('-');
        n = n * -1;
    }
    if (n >= base)
        multibase_put64(n / base, base);
    printf_handleNumberBaseWrite((n % base) + 0x30);
}

static void multibase_uput32(unsigned int n, u8_t base)
{
    if (n >= base)
        multibase_put32(n / base, base);
    printf_handleNumberBaseWrite((n % base) + 0x30);
}

static void multibase_uput64(unsigned long n, u8_t base)
{
    if (n >= base)
        multibase_put64(n / base, base);
    printf_handleNumberBaseWrite((n % base) + 0x30);
}

static void generic_puts(char const *s)
{
    for (int i = 0; s[i]; i++)
        printf_handleWrite(s[i]);
}

static inline int printf_getAlignement(char const **fmt)
{
    #define MAX_HANDLED_ALIGNEMENT 4
    char tmp[0x5];
    u32_t i = 0x0;

    while ((*fmt)[i] && (*fmt)[i] <= 0x39 && (*fmt)[i] >= 0x30) {
        if (i > MAX_HANDLED_ALIGNEMENT)
            return (0x0);
        tmp[i] = (*fmt)[i];
        i++;
    }
    tmp[i] = 0x0;
    *fmt += i;
    return (atoib(tmp, 10));
}

static inline void printf_AlignFormat(u32_t len)
{
    if (len > align)
        return;
    len = align - len;
    while (len > 1) {
        printf_handleWrite(0x30);
        len--;
    }
}

static void printf_handleIntegerFormatter(u64_t n, u8_t base)
{
    if (align) {
        u32_t len = numberlen(n, base);
        printf_AlignFormat(len);
    }
}

static void printf_handleStringFormatter(char const *s)
{
    if (align) { 
        u32_t len = strlen(s);
        printf_AlignFormat(len);
    }
}

static void printf_handleHashTag(u8_t base)
{
    if (!hshtag)
        return;
    switch (base) {
        case 16:
            generic_puts("0x");
            break;
        case 8:
            generic_puts("0o");
            break;
        case 2:
            generic_puts("0b");
            break;
        default:
            break;
    }
}
static void __generic_printf(char const *fmt, __builtin_va_list ap)
{
    while (*fmt)
    {
        if (*fmt != '%') {
            printf_handleWrite(*fmt);
        } else {
            fmt++;
            align  = false;
            hshtag = false;
            /* Formatter */
            bool flag = true;
            while (flag) {
                switch (*fmt) {
                    case '0':
                        fmt += 0x1;
                        align = printf_getAlignement(&fmt);
                        break;
                    case '#':
                        fmt += 0x1;
                        hshtag = true;
                        break;
                    default:
                        flag = false;
                        break;
                }
            }
            /* Init handled variable */
            int vint;
            uint vuint;
            long vlong;
            unsigned long vulong;
            char const *vcchar;
            /* flag handled by this generic printf */
            switch (*fmt) {
                case 's':
                    vcchar = __builtin_va_arg(ap, char const *);
                    printf_handleStringFormatter(vcchar);
                    generic_puts(vcchar);
                    break;
                case 'u':
                    vuint = __builtin_va_arg(ap, unsigned int);
                    printf_handleIntegerFormatter((u64_t)vuint, 10);
                    multibase_uput32(vuint, 10);
                    break;
                case 'U':
                    vulong = __builtin_va_arg(ap, unsigned long);
                    printf_handleIntegerFormatter((u64_t)vulong, 10);
                    multibase_uput32(vulong, 10);
                    break;
                case 'h':
                case 'd':
                case 'i':
                    vint = __builtin_va_arg(ap, int);
                    printf_handleIntegerFormatter((u64_t)vint, 10);
                    multibase_put32(vint, 10);
                    break;
                case 'x':
                    vint = __builtin_va_arg(ap, int);
                    printf_handleHashTag(16);
                    printf_handleIntegerFormatter((u64_t)vint, 16);
                    multibase_put32(vint, 16);
                    break;
                case 'o':
                    vint = __builtin_va_arg(ap, int);
                    printf_handleHashTag(8);
                    printf_handleIntegerFormatter((u64_t)vint, 8);
                    multibase_put32(vint, 8);
                    break;
                case 'b':
                    vint = __builtin_va_arg(ap, int);
                    printf_handleHashTag(2);
                    printf_handleIntegerFormatter((u64_t)vint, 2);
                    multibase_put32(vint, 2);
                    break;
                case 'l':
                    vlong = __builtin_va_arg(ap, long);
                    printf_handleIntegerFormatter((u64_t)vlong, 10);
                    multibase_put64(vlong, 10);
                    break;
                case 'X':
                    vlong = __builtin_va_arg(ap, unsigned long);
                    printf_handleHashTag(16);
                    printf_handleIntegerFormatter((u64_t)vlong, 16);
                    multibase_uput64(vlong, 16);
                    break;
                case 'O':
                    vlong = __builtin_va_arg(ap, long);
                    printf_handleHashTag(8);
                    printf_handleIntegerFormatter((u64_t)vlong, 8);
                    multibase_put64(vlong, 8);
                    break;
                case 'B':
                    vlong = __builtin_va_arg(ap, long);
                    printf_handleHashTag(2);
                    printf_handleIntegerFormatter((u64_t)vlong, 2);
                    multibase_put64(vlong, 2);
                    break;
                case 'c':
                    printf_handleWrite((char)__builtin_va_arg(ap, int));
                    break;
                case 'p':
                    vulong = (unsigned long)__builtin_va_arg(ap, void *);
                    printf_handleHashTag(16);
                    printf_handleIntegerFormatter((u64_t)vulong, 16);
                    multibase_uput64(vulong, 16);
                    break;
                #ifdef DEADLOCK_ARE_SOFUNNY
                    case 'F': /* take care of DEADLOCK if the function called use this printf its' over */
                        __builtin_va_arg(ap, void (*)(void))();
                        break;
                #endif
                case '%':
                    printf_handleWrite('%');
                    break;
                default: // unknow flag => print this
                    printf_handleWrite('%');
                    printf_handleWrite(*fmt);
            }
        }
        fmt++;
    }
}

#define GENERIC_PRINTF_INIT()       \
    if (!szputs)                    \
        return;                     \
    caller_szputs = szputs;         \
    align = false;

#define GENERIC_PRINTF_EXIT()    \
    printf_dumpBuffer();

void generic_vprintf(void (*szputs)(char const *, size_t), 
char const *fmt, __builtin_va_list ap)
{
    GENERIC_PRINTF_INIT();
    __generic_printf(fmt, ap);
    GENERIC_PRINTF_EXIT();
}

void generic_printf(void (*szputs)(char const *, size_t), 
char const *fmt, ...)
{
    GENERIC_PRINTF_INIT();
    __builtin_va_list ap;
    __builtin_va_start(ap, fmt);
    __generic_printf(fmt, ap);
    __builtin_va_end(ap);
    GENERIC_PRINTF_EXIT();
}

#undef GENERIC_PRINTF_INIT
#undef GENERIC_PRINTF_EXIT
#undef PRINTF_BUFFER_LENGHT