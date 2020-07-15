/******************************************************************************\
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _COSMOS_DEF_H_
# define _COSMOS_DEF_H_

# include <stdint.h>
# include <stddef.h>
# include <stdbool.h>

typedef unsigned char       uchar;
typedef unsigned short      ushort;
typedef unsigned int        uint;
typedef unsigned long       ulong;
typedef unsigned long long  ulonglong;

typedef int8_t          int8;
typedef int16_t         int16;
typedef int32_t         int32;
typedef int64_t         int64;
typedef intptr_t        intptr;
typedef intptr_t        ssize_t;

typedef uint8_t         uint8;
typedef uint16_t        uint16;
typedef uint32_t        uint32;
typedef uint64_t        uint64;
typedef uintptr_t       uintptr;

typedef int8_t          s8_t;
typedef int16_t         s16_t;
typedef int32_t         s32_t;
typedef int64_t         s64_t;

typedef uint8_t         u8_t;
typedef uint16_t        u16_t;
typedef uint32_t        u32_t;
typedef uint64_t        u64_t;

typedef void *          virtaddr_t;
typedef uintptr_t       physaddr_t;

typedef uintptr         archv_t;
typedef uintptr *       archp_t;

typedef struct { volatile int counter; } atomic_t;

#define restrict        __restrict
#define __pure          __attribute__((pure))
#define __const         __attribute__((const))
#define __cold          __attribute__((cold))
#define __hot           __attribute__((hot))
#define __used          __attribute__((used))
#define __unused        __attribute__((unused))
#define __packed        __attribute__((packed))
#define __weak          __attribute__((weak))
#define __aligned(x)    __attribute__((aligned (x)))
#define __section(s)    __attribute__((section (s)))
#define __noreturn      __attribute__((noreturn))
#define __expected(x)   __builtin_expect((x), 1)
#define __unexpected(x) __builtin_expect((x), 0)
#define __optimize(x)   __attribute__((optimize(x)))

#endif /* _COSMOS_DEF_H_ */