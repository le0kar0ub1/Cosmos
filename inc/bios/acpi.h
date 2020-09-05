/******************************************************************************
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

#ifndef _BIOS_ACPI_H_
# define _BIOS_ACPI_H_

# include <cosmos.h>

#define ACPI_SIG_DSDT           "DSDT"	/* Differentiated System Description Table */
#define ACPI_SIG_FADT           "FACP"	/* Fixed ACPI Description Table */
#define ACPI_SIG_FACS           "FACS"	/* Firmware ACPI Control Structure */
#define ACPI_SIG_OSDT           "OSDT"	/* Override System Description Table */
#define ACPI_SIG_PSDT           "PSDT"	/* Persistent System Description Table */
#define ACPI_SIG_RSDP           "RSD PTR "	/* Root System Description Pointer */
#define ACPI_SIG_RSDT           "RSDT"	/* Root System Description Table */
#define ACPI_SIG_XSDT           "XSDT"	/* Extended  System Description Table */
#define ACPI_SIG_SSDT           "SSDT"	/* Secondary System Description Table */
#define ACPI_RSDP_NAME          "RSDP"	/* Short name for RSDP, not signature */
#define ACPI_OEM_NAME           "OEM"	/* Short name for OEM, not signature */

struct rsdp_desc_v1
{
	char signature[8];
	u8_t checksum;
	char oemidi[6];
	u8_t revision;
	u32_t rsdt_phys_addr;
} __packed;

struct rsdp_desc_v2
{
	struct rsdp_desc_v1 rsdpv1;
	u32_t lenght;
	u64_t xsdt_phys_addr;
	u8_t extended_checksum;
	u8_t reserved[3];
} __packed;

struct sdt_header
{
	char signature[4];
	u32_t lenght;
	u8_t revision;
	u8_t checksum;
	char oemid[6];
	char oemidTable[8];
	u32_t oem_revision;
	u32_t creator_id;
	u32_t creator_revision;
} __packed;

struct rsdt
{
	struct sdt_header hdr;
	u32_t sdt_phys_addr[];
};

struct xsdt
{
	struct sdt_header hdr;
	u64_t sdt_phys_addr[];
};

struct acpi_generic_address
{
	u8_t space_id;		/* Address space where struct or register exists */
	u8_t bit_width;		/* Size in bits of given register */
	u8_t bit_offset;		/* Bit offset within the register */
	u8_t access_width;	/* Minimum Access size (ACPI 3.0) */
	u64_t address;		/* 64-bit address of struct or register */
};

struct acpi_table_fadt
{
	struct sdt_header header;	/* Common ACPI table header */
	u32_t facs;		/* 32-bit physical address of FACS */
	u32_t dsdt;		/* 32-bit physical address of DSDT */
	u8_t model;		/* System Interrupt Model (ACPI 1.0) - not used in ACPI 2.0+ */
	u8_t preferred_profile;	/* Conveys preferred power management profile to OSPM. */
	u16_t sci_interrupt;	/* System vector of SCI interrupt */
	u32_t smi_command;	/* 32-bit Port address of SMI command port */
	u8_t acpi_enable;		/* Value to write to SMI_CMD to enable ACPI */
	u8_t acpi_disable;	/* Value to write to SMI_CMD to disable ACPI */
	u8_t s4_bios_request;	/* Value to write to SMI_CMD to enter S4BIOS state */
	u8_t pstate_control;	/* Processor performance state control */
	u32_t pm1a_event_block;	/* 32-bit port address of Power Mgt 1a Event Reg Blk */
	u32_t pm1b_event_block;	/* 32-bit port address of Power Mgt 1b Event Reg Blk */
	u32_t pm1a_control_block;	/* 32-bit port address of Power Mgt 1a Control Reg Blk */
	u32_t pm1b_control_block;	/* 32-bit port address of Power Mgt 1b Control Reg Blk */
	u32_t pm2_control_block;	/* 32-bit port address of Power Mgt 2 Control Reg Blk */
	u32_t pm_timer_block;	/* 32-bit port address of Power Mgt Timer Ctrl Reg Blk */
	u32_t gpe0_block;		/* 32-bit port address of General Purpose Event 0 Reg Blk */
	u32_t gpe1_block;		/* 32-bit port address of General Purpose Event 1 Reg Blk */
	u8_t pm1_event_length;	/* Byte Length of ports at pm1x_event_block */
	u8_t pm1_control_length;	/* Byte Length of ports at pm1x_control_block */
	u8_t pm2_control_length;	/* Byte Length of ports at pm2_control_block */
	u8_t pm_timer_length;	/* Byte Length of ports at pm_timer_block */
	u8_t gpe0_block_length;	/* Byte Length of ports at gpe0_block */
	u8_t gpe1_block_length;	/* Byte Length of ports at gpe1_block */
	u8_t gpe1_base;		/* Offset in GPE number space where GPE1 events start */
	u8_t cst_control;		/* Support for the _CST object and C-States change notification */
	u16_t c2_latency;		/* Worst case HW latency to enter/exit C2 state */
	u16_t c3_latency;		/* Worst case HW latency to enter/exit C3 state */
	u16_t flush_size;		/* Processor memory cache line width, in bytes */
	u16_t flush_stride;	/* Number of flush strides that need to be read */
	u8_t duty_offset;		/* Processor duty cycle index in processor P_CNT reg */
	u8_t duty_width;		/* Processor duty cycle value bit width in P_CNT register */
	u8_t day_alarm;		/* Index to day-of-month alarm in RTC CMOS RAM */
	u8_t month_alarm;		/* Index to month-of-year alarm in RTC CMOS RAM */
	u8_t century;		/* Index to century in RTC CMOS RAM */
	u16_t boot_flags;		/* IA-PC Boot Architecture Flags (see below for individual flags) */
	u8_t reserved;		/* Reserved, must be zero */
	u32_t flags;		/* Miscellaneous flag bits (see below for individual flags) */
	struct acpi_generic_address reset_register;	/* 64-bit address of the Reset register */
	u8_t reset_value;		/* Value to write to the reset_register port to reset the system */
	u16_t arm_boot_flags;	/* ARM-Specific Boot Flags (see below for individual flags) (ACPI 5.1) */
	u8_t minor_revision;	/* FADT Minor Revision (ACPI 5.1) */
	u64_t Xfacs;		/* 64-bit physical address of FACS */
	u64_t Xdsdt;		/* 64-bit physical address of DSDT */
	struct acpi_generic_address xpm1a_event_block;	/* 64-bit Extended Power Mgt 1a Event Reg Blk address */
	struct acpi_generic_address xpm1b_event_block;	/* 64-bit Extended Power Mgt 1b Event Reg Blk address */
	struct acpi_generic_address xpm1a_control_block;	/* 64-bit Extended Power Mgt 1a Control Reg Blk address */
	struct acpi_generic_address xpm1b_control_block;	/* 64-bit Extended Power Mgt 1b Control Reg Blk address */
	struct acpi_generic_address xpm2_control_block;	/* 64-bit Extended Power Mgt 2 Control Reg Blk address */
	struct acpi_generic_address xpm_timer_block;	/* 64-bit Extended Power Mgt Timer Ctrl Reg Blk address */
	struct acpi_generic_address xgpe0_block;	/* 64-bit Extended General Purpose Event 0 Reg Blk address */
	struct acpi_generic_address xgpe1_block;	/* 64-bit Extended General Purpose Event 1 Reg Blk address */
	struct acpi_generic_address sleep_control;	/* 64-bit Sleep Control register (ACPI 5.0) */
	struct acpi_generic_address sleep_status;	/* 64-bit Sleep Status register (ACPI 5.0) */
	u64_t hypervisor_id;	/* Hypervisor Vendor ID (ACPI 6.0) */
};

void acpi_enable(void);
void acpi_disable(void);
void acpi_fadt_init(void);

struct acpi_table_madt
{
	struct sdt_header header;
	u32_t loc_apic_addr;
	u32_t flags;
} __packed;

enum acpi_madt_entry_type
{
	ACPI_MADT_ENTRY_TYPE_0,
	ACPI_MADT_ENTRY_TYPE_1,
	ACPI_MADT_ENTRY_TYPE_2,
	ACPI_MADT_ENTRY_TYPE_4,
	ACPI_MADT_ENTRY_TYPE_5,
};

struct acpi_madt_et_flag
{
	u8_t entry_type;
	u8_t record_lenght;
};

/*
 * single physical core & local interrupt controller
 */
struct acpi_madt_et0_cpu_loc_apic
{
	struct acpi_madt_et_flag header;
	u8_t acpi_cpu_id;
	u8_t apic_id;
	u32_t flags; // bit 0 = cpu enabled, bit 1 = online capable
} __packed;

/*
 * single IOAPIC
 */
struct acpi_madt_et1_ioapic
{
	struct acpi_madt_et_flag header;
	u8_t ioapic_id;
	u8_t _reserved;
	u32_t ioapic_addr;
	u32_t glob_sys_int_base;
} __packed;

/*
 * Interrupt source overriding
 */
struct acpi_madt_et2_int_src_override
{
	struct acpi_madt_et_flag header;
	u8_t bus_src;
	u8_t irq_src;
	u32_t glob_sys_int;
	u16_t flags;
} __packed;

/*
 * LVT NMI
 */
struct acpi_madt_et4_nmi
{
	struct acpi_madt_et_flag header;
	u8_t acpi_cpu_id;
	u16_t flags;
	u8_t lint;
} __packed;

/*
 * 64 bits system override local apic
 */
struct acpi_madt_et5_apic_addr_override
{
	struct acpi_madt_et_flag header;
	u16_t _reserved;
	u64_t loc_apic_addr;
} __packed;

void acpi_init(void);
virtaddr_t acpi_get_table(char const *signature);

#endif /* !_BIOS_ACPI_H_ */
