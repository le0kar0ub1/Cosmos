/********************************************************************************
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include <kernel/def/def.h>
# include <kernel/drivers/drivers.h>
# include <kernel/init/inithooks.h>
# include <drivers/vga.h>
# include <bios/acpi.h>
# include <arch/x86_64/boot/multiboot2.h>
# include <arch/x86_64/mem/vmm.h>
# include <arch/x86_64/system/apic.h>
# include <arch/x86_64/system/ioapic.h>

/*
** Cosmos signature & acquired start
*/
static void helloFromCosmos(void)
{
    vga_set_color(VGA_BLACK, VGA_LIGHT_BLUE);
    vga_puts(cosmos_signature_asciiart);
    vga_set_color(VGA_BLACK, VGA_WHITE);
    vga_puts("\nkernel init routine...");
}

static void boot_hook(void)
{
    multiboot_parse_tags();
    driver_probe_runhook(COSMOS_HOOK_BOOT);
    helloFromCosmos();
    /*
    ** The following initializations depend of the first above
    */
    x86_64_vmm_init();
    acpi_init();
    apic_init();
    ioapic_init();
}

REGISTER_BOOT_INITHOOK(boot_hook);
