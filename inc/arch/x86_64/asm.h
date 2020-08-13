/******************************************************************************
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _ARCH_x86_64_ASM_H_
# define _ARCH_x86_64_ASM_H_

# include <kernel/def/def.h>

typedef volatile uint32 atomic32_t;
typedef volatile uint64 atomic64_t;

typedef atomic32_t kref_t;

# define atomic_xadd(P, V)      __sync_fetch_and_add((P), (V))
# define cmpxchg(P, O, N)       __sync_val_compare_and_swap((P), (O), (N))
# define atomic_inc(P)          __sync_add_and_fetch((P), 1)
# define atomic_dec(P)          __sync_add_and_fetch((P), -1) 
# define atomic_add(P, V)       __sync_add_and_fetch((P), (V))
# define atomic_set_bit(P, V)   __sync_or_and_fetch((P), 1 << (V))
# define atomic_clear_bit(P, V) __sync_and_and_fetch((P), ~( 1<< (V)))

/* Compile read-write barrier */
# define barrier() asm volatile("": : :"memory")

/* Pause instruction to prevent excess processor bus usage */ 
# define cpu_relax() asm volatile("pause\n": : :"memory")

/*
** Read a register
*/
# define read_xreg(reg, into)                      \
            asm volatile(                          \
                "mov %%"#reg",%0" : "=r"(into)     \
            );

/*
** Write a register
*/
# define write_xreg(reg, from)                     \
            asm volatile(                          \
                "mov %0, %%"#reg : "=r"(from)      \
            );

/* Atomic exchange (of various sizes) */
static inline void *xchg_64(void *ptr, void *x)
{
    asm volatile("xchgq %0,%1"
            :"=r" ((uintptr) x)
            :"m" (*(volatile uintptr *)ptr), "0" ((uintptr) x)
            :"memory");
    return x;
}

static inline unsigned xchg_32(void *ptr, unsigned x)
{
    asm volatile("xchgl %0,%1"
            :"=r" ((unsigned) x)
            :"m" (*(volatile unsigned *)ptr), "0" (x)
            :"memory");
    return x;
}

static inline unsigned short xchg_16(void *ptr, unsigned short x)
{
    asm volatile("xchgw %0,%1"
            :"=r" ((unsigned short) x)
            :"m" (*(volatile unsigned short *)ptr), "0" (x)
            :"memory");
    return x;
}

static inline uint xchg(uint volatile *addr, uint newval)
{
    uint res;

    asm volatile("lock xchgl %0, %1;" : "+m"(*addr), "=a"(res) : "1"(newval) : "cc");
    return (res);
}

/* Test and set a bit */
static inline char atomic_bitsetandtest(void *ptr, int x)
{
    char out;
    asm volatile("lock; bts %2,%1\n"
            "sbb %0,%0\n"
            :"=r" (out), "=m" (*(volatile uintptr *)ptr)
            :"Ir" (x)
            :"memory");
    return out;
}

static inline uint atomic_exchange(volatile uint *ptr, uint value)
{
    return (xchg(ptr, value));
}

static inline uint32 atomic_read32(atomic32_t *var)
{
    return __atomic_load_n(var, __ATOMIC_SEQ_CST);
}

static inline uint32 atomic_inc_read32(atomic32_t *var)
{
    return __atomic_add_fetch(var, 1, __ATOMIC_SEQ_CST);
}

static inline uint32 atomic_dec_read32(atomic32_t *var)
{
    return __atomic_sub_fetch(var, 1, __ATOMIC_SEQ_CST);
}

static inline void atomic_write32(atomic32_t *var, uint32 val)
{
    __atomic_store_n(var, val, __ATOMIC_SEQ_CST);
}


static inline uint64 atomic_read64(atomic64_t *var)
{
    return __atomic_load_n(var, __ATOMIC_SEQ_CST);
}

static inline uint64 atomic_inc_read64(atomic64_t *var)
{
    return __atomic_add_fetch(var, 1, __ATOMIC_SEQ_CST);
}

static inline uint64 atomic_dec_read64(atomic64_t *var)
{
    return __atomic_sub_fetch(var, 1, __ATOMIC_SEQ_CST);
}

static inline void atomic_write64(atomic64_t *var, uint32 val)
{
    __atomic_store_n(var, val, __ATOMIC_SEQ_CST);
}

static inline void kref_inc(kref_t *k)
{
    atomic_inc_read32(k);
}

static inline void kref_dec(kref_t *k)
{
    atomic_dec_read32(k);
}

static inline uint32 kref_inc_read(kref_t *k)
{
    return atomic_inc_read32(k);
}

static inline uint32 kref_dec_read(kref_t *k)
{
    return atomic_dec_read32(k);
}

static inline uint32 kref_read(kref_t *k)
{
    return atomic_read32(k);
}

static inline void invlpg(void *p)
{
    asm volatile("invlpg (%0)" : : "r"(p) : "memory");
}

static inline uintptr get_cr2(void)
{
    uintptr out;
    asm volatile("mov %%cr2, %0" : "=a"(out));
    return (out);
}

static inline uintptr get_cr3(void)
{
    uintptr out;
    asm volatile("mov %%cr3, %0" : "=a"(out));
    return (out);
}

static inline void set_cr3(uintptr cr3)
{
    asm volatile("mov %0, %%cr3" :: "r"(cr3));
}

static inline uintptr get_cr4(void)
{
    uintptr out;
    asm volatile("mov %%cr4, %0" : "=a"(out));
    return (out);
}

static inline void set_cr4(uintptr cr4)
{
    asm volatile("mov %0, %%cr4" :: "r"(cr4));
}

static inline uintptr get_cr0(void)
{
    uintptr out;
    asm volatile("mov %%cr0, %0" : "=a"(out));
    return (out);
}

static inline void set_cr0(uintptr cr0)
{
    asm volatile("mov %0, %%cr0" :: "r"(cr0));
}

static inline uint64 rdtsc(void)
{
    uint64 ret;
    asm volatile("rdtsc" : "=A"(ret));
    return (ret);
}

static inline void cpuid(uint32 id, uint32 *eax, uint32 *edx)
{
    asm volatile("cpuid" : "=a"(*eax), "=d"(*edx) : "a"(id) : "ebx", "ecx");
}

/* wait an interrupt */
static inline void hlt(void)
{
    asm volatile("hlt");
}

/* pushfq/popfq instruction*/
static inline void pushfq(void)
{
    asm volatile("pushfq");
}

static inline void popfq(void)
{
    asm volatile("popfq");
}

/* enable interruption */
static inline void sti(void)
{
    asm volatile("sti");
}

/* disable interruption */
static inline void cli(void)
{
    asm volatile("cli");
}

/* enable direction flag */
static inline void std(void)
{
    asm volatile("std");
}

/* disable direction flag */
static inline void cld(void)
{
    asm volatile("cld");
}

/* force a thread to sleep */
static inline void pause(void)
{
    asm volatile("pause");
}

/* fire an interrupt */
static inline void interrupt(uchar vector)
{
    asm volatile("int %0" :: "i"(vector));
}

static inline uint64 read_rflags(void)
{
    return (__builtin_ia32_readeflags_u64());
}
static inline void write_rflags(uint64 rflags)
{
    __builtin_ia32_writeeflags_u64(rflags);
}

static inline uint64 get_rflags(void)
{
    uint64 e;

    asm volatile("pushfq; pop %0" : "=rm"(e) :: "memory");
    return (e);
}

static inline void set_rflags(uint64 value)
{
    asm volatile("push %0; popfq" :: "g"(value) : "memory", "cc");
}


static inline void preempt_inc(void)
{
    asm volatile("lock incl %%gs:0x18" :: );
}

static inline void preempt_dec(void)
{
    asm volatile("lock decl %%gs:0x18" :: );
}

static inline void io_delay(void)
{
    asm volatile("outb %%al, $0x80" : : "a"(0));
}

#endif /* _ARCH_x86_64_ASM_H_ */