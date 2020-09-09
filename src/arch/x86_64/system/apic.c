/********************************************************************************
** 
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include <cosmos.h>
# include <kernel/mem/kalloc.h>
# include <kernel/io/mem.h>
# include <kernel/io/port.h>
# include <arch/x86_64/system/apic.h>
# include <arch/x86_64/cpu/cpuid.h>
# include <arch/x86_64/asm.h>
# include <arch/x86_64/interrupts/interrupts.h>

static volatile u32_t *apic = NULL;

REGISTER_IO_PORT(
	port_icmr_address,
	0x22
);

REGISTER_IO_PORT(
	port_icmr_data,
	0x23
);

/*
 * write the given value to the given register
 */
static void apic_write_reg(enum apic_reg reg, u32_t val)
{
	*((volatile u32_t *)ADD_PTR(apic, reg)) = val;
}

/*
 * read a value on the given register
 */
static u32_t apic_read_reg(enum apic_reg reg)
{
	return (*((volatile u32_t *)ADD_PTR(apic, reg)));
}

/*
 * Get the APIC id og the running processor
 */
u32_t apic_get_id(void)
{
	return ((u32_t)(apic_read_reg(APIC_ID) >> 24));
}

/*
 * static micro-wait for SMP init
 */
static void rdtsc_mwait(void)
{
	u64_t start = rdtsc();

	while (rdtsc() < start +  300000000ul);
}

/*
 * Signal APIC EndOfInterrupt
 */
void apic_eoi(void)
{
	apic_write_reg(APIC_EOI, 0x0);
}

/*
 * Send IPI to the given local APIC
 */
void apic_send_ipi(u32_t apicid, u32_t attrib)
{
	apic_write_reg(APIC_ICR_HIGH, apicid << 24u);
	apic_write_reg(APIC_ICR_LOW, attrib);
}

/*
 * Enable xAPIC by writing MSR
 */
static void apic_enable(void)
{
	u64_t msr;

	msr = msr_read(MSR_APIC_BASE);
  	msr |= (1 << 11u);
    msr_write(MSR_APIC_BASE, msr);
}

/*
 * Enable x2APIC by writing MSR
 */
static void x2apic_enale(void)
{
	u64_t msr;

	msr = msr_read(MSR_APIC_BASE);
	msr |= (1 << 10u);
	msr_write(MSR_APIC_BASE, msr);
}

/*
 * Initialize de Local APIC
 */
void apic_init(void)
{
	if (!cpuid_get_edx_feature(CPUID_FEAT_EDX_APIC))
		panic("APIC feature isn't available");
	/*
     * DO NOT PANIC if x2APIC isn't available
     * We will probably not implement x2apic in this kernel
     * The improvements done for x2apic aren't relevant for us
     */
	//if (!cpuid_get_ecx_feature(CPUID_FEAT_ECX_x2APIC))
	//    panic("x2APIC unavailable");
	apic = kmap_dev(APIC_PHYS_BASE_ADDR, KCONFIG_MMU_PAGESIZE);
	assert(apic);

	/* 
     * Enable Local APIC by setting spurious interrupt vector
     */
	apic_write_reg(APIC_SIV, APIC_SVR_ENABLED | INT_APIC_SPURIOUS);

	/* 
     * Mask unused interrupts
     * Locanl interrupt 0/1 & the perf counter
     */
	apic_write_reg(APIC_LVT_LINT0, APIC_LVT_MASKED);
	apic_write_reg(APIC_LVT_LINT1, APIC_LVT_MASKED);
	apic_write_reg(APIC_LVT_PERFCOUNT, APIC_LVT_MASKED);

	/* 
     * Set up apic Timer
     */
	apic_write_reg(APIC_TIMER_DCR, APIC_TIMER_X8);
	apic_write_reg(APIC_LVT_TIMER, APIC_TIMER_PERIODIC | INT_APIC_TIMER);
	apic_write_reg(APIC_TIMER_ICR, 10000000);

	/*
     * Map error interrupt
     */
	apic_write_reg(APIC_LVT_ERROR, INT_APIC_ERROR);

	/*
     * Register interrupt handlers
     */
	interrupt_register_handler(INT_APIC_TIMER, &apic_timer_interrupt_handler);
	interrupt_register_handler(INT_APIC_ERROR, &apic_error_interrupt_handler);
	interrupt_register_handler(INT_APIC_SPURIOUS, &apic_spurious_interrupt_handler);

	/*
     * Clear Error Status Register
     */
	apic_write_reg(APIC_ESR, 0x0);
	apic_write_reg(APIC_ESR, 0x0);

	/*
     * Clear any outstanding interrupts
     */
	apic_write_reg(APIC_EOI, 0x0);

	/*
     * Clear task priority to enable all interrupts
     */
	apic_write_reg(APIC_TPR, 0x0);

	apic_enable();
}

REGISTER_IO_PMM(
	phys_apic,
	APIC_PHYS_BASE_ADDR,
	(APIC_PHYS_BASE_ADDR + KCONFIG_MMU_PAGESIZE),
	RW
);
