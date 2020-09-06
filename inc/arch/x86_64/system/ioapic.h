/******************************************************************************
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _ARCH_x86_64_SYSTEM_IOAPIC_H_
# define _ARCH_x86_64_SYSTEM_IOAPIC_H_

# include <cosmos.h>


#define IOAPIC_PHYS_BASE_ADDR ((physaddr_t)0x0FEC00000)

/*
 * All I/O APIC register offset
 */
enum ioapic_reg
{
	IOAPIC_ID		= 0x00,		/* ID */
	IOAPIC_VERSION	= 0x01,		/* Version */
	IOAPIC_TABLE	= 0x10,		/* Table base */
};

union ioapic_id_reg
{
	struct
	{
		u32_t _reserved0  : 26;
		u32_t dev_apic_id : 4;
		u32_t _reserved1  : 2;
	};
	u32_t value;
} __packed;

static_assert(sizeof(union ioapic_id_reg) == sizeof(u32_t));

union ioapic_version_reg
{
	struct
	{
		u32_t version    : 8;
		u32_t _reserved0 : 8;
		u32_t maxirqs    : 8;
		u32_t _reserved1 : 8;
	};
	u32_t value;
} __packed;

static_assert(sizeof(union ioapic_version_reg) == sizeof(u32_t));

union ioapic_entry
{
	struct {
		u32_t vector : 8;	/* Allowed values from 0x10 to 0xFE */
		u32_t delivery_mode : 3;	/* Type of delivery mode */
		u32_t destination_mode : 1;	/* 0 = physical mode, 1 = logical mode */
		u32_t const delivery_status : 1; /* Set if APIC is busy */
		u32_t polarity : 1;
		u32_t const received : 1;
		u32_t trigger_mode : 1;	/* 0 = edge sensitive, 1 = level sensitive */
		u32_t mask : 1;		/* Set to mask the interrupt */
		u32_t _reserved0 : 15;
		u32_t _reserved1 : 24;
		u32_t destination : 8;
	};
	struct {
		u32_t low32;
		u32_t high32;
	};
	u64_t value;
};

static_assert(sizeof(union ioapic_entry) == sizeof(u64_t));

/* 
 * Delivery mode 
 */
enum ioapic_delivery_mode
{
	IOAPIC_DELIVERY_MODE_FIXED	= 0x0,
	IOAPIC_DELIVERY_MODE_LOWPR	= 0x1,
	IOAPIC_DELIVERY_MODE_SMI	= 0x2,
	IOAPIC_DELIVERY_MODE_NMI	= 0x4,
	IOAPIC_DELIVERY_MODE_INIT	= 0x5,
	IOAPIC_DELIVERY_MODE_EXTINT	= 0x7,
};

/* 
 * Destination mode
 */
enum ioapic_dest_mode
{
	IOAPIC_DEST_MODE_PHYSICAL	= 0x0,
	IOAPIC_DEST_MODE_LOGICAL	= 0x1,
};

/*
 * Interrupt Input Pin Polarity
 */
enum ioapic_polarity
{
	IOAPIC_POLARITY_HIGH		= 0x0,
	IOAPIC_POLARITY_LOW 		= 0x1,
};

/* 
 * Trigger Mode (R/W)
 */
enum ioapic_trigger
{
	IOAPIC_TRIGGER_EDGE		= 0x0,
	IOAPIC_TRIGGER_LEVEL	= 0x1,
};

/* 
 * Interrupt Mask (R/W)
 */
enum ioapic_mask
{
	IOAPIC_UNMASK		= 0x0,
	IOAPIC_MASK			= 0x1,
};

/*
 * Message Destination Address (APIC logical destination mode)
 */
enum ioapic_dest_type
{
	IOAPIC_DEST_BROADCAST		= 0xff,
};

void ioapic_mask_vector(u32_t vector);
void ioapic_unmask_vector(u32_t vector);
void ioapic_init(void);

#endif /* !_ARCH_x86_64_SYSTEM_IOAPIC_H_ */
