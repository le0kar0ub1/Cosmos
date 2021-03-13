/********************************************************************************
**
**  This file is part of the Cosmos project, and is made available under
**  the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2020 - Leo Karoubi
**
\******************************************************************************/

# include <arch/x86_64/boot/multiboot2.h>
# include <drivers/uart16650.h>

// https://www.gnu.org/software/grub/manual/multiboot2/multiboot.html

struct multiboot_info multiboot;

uintptr_t multiboot_virtaddr = 0x0;

/*
** Parse the multiboot structure
*/
void multiboot_parse_tags(void)
{
    if (!multiboot_virtaddr || multiboot_virtaddr & 0x7) {
        uart16650_printf("Inalid multiboot header address\n");
        return;
    }
    /* skip the useless 8 bytes header */
    struct multiboot_tag *tag = (struct multiboot_tag *) (multiboot_virtaddr + 0x8);
    while (tag->type != MULTIBOOT_TAG_TYPE_END) {
        switch (tag->type)
        {
        case MULTIBOOT_TAG_TYPE_CMDLINE:
            multiboot.cmd_line = ((struct multiboot_tag_string *) tag)->string;
            break;
        case MULTIBOOT_TAG_TYPE_BOOT_LOADER_NAME: /* Loader Name */
            multiboot.bootloader = ((struct multiboot_tag_string *) tag)->string;
            break;
        case MULTIBOOT_TAG_TYPE_BASIC_MEMINFO: /* memory used */
            multiboot.mem_lower = ((struct multiboot_tag_basic_meminfo *) tag)->mem_lower;
            multiboot.mem_upper = ((struct multiboot_tag_basic_meminfo *) tag)->mem_upper;
            break;
        case MULTIBOOT_TAG_TYPE_MMAP: /* memory map */
            multiboot.mmap_start = (struct multiboot_mmap_entry *)((struct multiboot_tag_mmap const *)tag)->entries;
            multiboot.mmap_end = (struct multiboot_mmap_entry *)(struct multiboot_mmap_entry const *)((uchar const *)tag + tag->size);
            multiboot.mmap_entry_size = ((struct multiboot_tag_mmap const *)tag)->entry_size;
            break;
        case MULTIBOOT_TAG_TYPE_MODULE: /* no modules loaded */
            /* use it to load data at entry (later) */
            uart16650_printf("Module at %x to %x. Command line %s\n",
            ((struct multiboot_tag_module *) tag)->mod_start,
            ((struct multiboot_tag_module *) tag)->mod_end,
            ((struct multiboot_tag_module *) tag)->cmdline);
            break;
        case MULTIBOOT_TAG_TYPE_ACPI_OLD:
            break;
        case MULTIBOOT_TAG_TYPE_ACPI_NEW:
            break;
        }
        /* next tag */
        tag = (struct multiboot_tag *) ((uchar const *)tag + ((tag->size + 7) & ~7));
    }
}