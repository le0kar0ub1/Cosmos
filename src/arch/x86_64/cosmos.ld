OUTPUT_FORMAT(elf64-x86-64);
ENTRY(_start)

PROVIDE(__KERNEL_ADDR_TRNS = 0xFFFFFFFF80000000);
PROVIDE(__KERNEL_VIRT_LINK = 0xFFFFFFFF80100000);
PROVIDE(__KERNEL_PHYS_LINK = 0x0000000000100000);

SECTIONS
{
    . = __KERNEL_VIRT_LINK;

    /*
    ** Ensure multiboot header is at the very beginning
    */
    .multiboot ALIGN(0x1000) : AT(ADDR(.multiboot) - __KERNEL_ADDR_TRNS)
    {
        KEEP(*(.multiboot))
    }

    /*
    ** Ensure that these datas are at the beginning
    */
    .bootstrap ALIGN(0x1000) : AT(ADDR(.bootstrap) - __KERNEL_ADDR_TRNS)
    {
        *(.boot.text)
        *(.boot.data)
        *(.boot.rodata)
    }

    .text ALIGN(0x1000) : AT(ADDR(.text) - __KERNEL_ADDR_TRNS)
    {
        PROVIDE(__start_text_ = .);
        *(.text)
        PROVIDE(__end_text_ = .);
    }

    /*
    ** section initcalls, used to register functions to call by init level
    */
    .initcall ALIGN(0x8) : AT(ADDR(.initcall) - __KERNEL_ADDR_TRNS)
    {
        PROVIDE(__initcall_start = .);

        PROVIDE(__initcall0_start = .);
        KEEP(*(.initcall_0.text));
        PROVIDE(__initcall0_end = .);

        PROVIDE(__initcall1_start = .);
        KEEP(*(.initcall_1.text));
        PROVIDE(__initcall1_end = .);

        PROVIDE(__initcall2_start = .);
        KEEP(*(.initcall_2.text));
        PROVIDE(__initcall2_end = .);

        PROVIDE(__initcall3_start = .);
        KEEP(*(.initcall_3.text));
        PROVIDE(__initcall3_end = .);

        PROVIDE(__initcall4_start = .);
        KEEP(*(.initcall_4.text));
        PROVIDE(__initcall4_end = .);

        PROVIDE(__initcall5_start = .);
        KEEP(*(.initcall_5.text));
        PROVIDE(__initcall5_end = .);

        PROVIDE(__initcall6_start = .);
        KEEP(*(.initcall_6.text));
        PROVIDE(__initcall6_end = .);

        PROVIDE(__initcall7_start = .);
        KEEP(*(.initcall_7.text));
        PROVIDE(__initcall7_end = .);

        PROVIDE(__initcall8_start = .);
        KEEP(*(.initcall_8.text));
        PROVIDE(__initcall8_end = .);

        PROVIDE(__initcall9_start = .);
        KEEP(*(.initcall_9.text));
        PROVIDE(__initcall9_end = .);

        PROVIDE(__initcall_end = .);
    }

    /*
    ** section inithook, used to register functions wich will be init each hook level
    */
    .inithook ALIGN(0x8) : AT(ADDR(.inithook) - __KERNEL_ADDR_TRNS)
    {
        PROVIDE(__inithook_start = .);
        KEEP(*(.inithook_0.text));
        PROVIDE(__inithook0 = .);
        KEEP(*(.inithook_1.text));
        PROVIDE(__inithook1 = .);
        KEEP(*(.inithook_2.text));
        PROVIDE(__inithook2 = .);
        KEEP(*(.inithook_3.text));
        PROVIDE(__inithook3 = .);
        KEEP(*(.inithook_4.text));
        PROVIDE(__inithook4 = .);
        KEEP(*(.inithook_5.text));
        PROVIDE(__inithook5 = .);
        KEEP(*(.inithook_6.text));
        PROVIDE(__inithook6 = .);
        KEEP(*(.inithook_7.text));
        PROVIDE(__inithook7 = .);
        KEEP(*(.inithook_8.text));
        PROVIDE(__inithook8 = .);
        KEEP(*(.inithook_9.text));
        PROVIDE(__inithook9 = .);
        PROVIDE(__inithook_end = .);
    }

    /*
    ** mark physical memory areas as system-reserved
    */
    .pmm_reserved_area ALIGN(0x8) : AT(ADDR(.pmm_reserved_area) - __KERNEL_ADDR_TRNS)
    {
        PROVIDE(__pmm_reserved_area_start = .);
        KEEP(*(.pmm_reserved_area));
        PROVIDE(__pmm_reserved_area_end = .);
    }

    /*
    ** register used io port
    */
    .cosmos_io_port ALIGN(0x8) : AT(ADDR(.cosmos_io_port) - __KERNEL_ADDR_TRNS)
    {
        PROVIDE(__cosmos_io_port_start = .);
        KEEP(*(.cosmos_io_port));
        PROVIDE(__cosmos_io_port_end = .);
    }

    /*
    ** mark physical memory areas as system-reserved
    */
    .cosmos_io_mem ALIGN(0x8) : AT(ADDR(.cosmos_io_mem) - __KERNEL_ADDR_TRNS)
    {
        PROVIDE(__cosmos_io_mem_start = .);
        KEEP(*(.cosmos_io_mem));
        PROVIDE(__cosmos_io_mem_end = .);
    }

    .rodata ALIGN(0x1000) : AT(ADDR(.rodata) - __KERNEL_ADDR_TRNS)
    {
        PROVIDE(__start_rodata_ = .);
        *(.rodata)
        PROVIDE(__end_rodata_ = .);
    }

    .data ALIGN(0x1000) : AT(ADDR(.data) - __KERNEL_ADDR_TRNS)
    {
        PROVIDE(__start_data_ = .);
        *(.data)
        PROVIDE(__end_data_ = .);
    }

    PROVIDE(__VIRT_BSS_START = .);
    PROVIDE(__PHYS_BSS_START = . - __KERNEL_ADDR_TRNS);
    .bss ALIGN(0x1000) : AT(ADDR(.bss) - __KERNEL_ADDR_TRNS)
    {
        PROVIDE(__start_bss_ = .);
        *(.bss)
        PROVIDE(__end_bss_ = .);
    }
    PROVIDE(__VIRT_BSS_END = .);
    PROVIDE(__PHYS_BSS_END = . - __KERNEL_ADDR_TRNS);
    PROVIDE(__BSS_SIZE = __BSS_END - __BSS_START);

    . = ALIGN(0x1000);
    PROVIDE(__KERNEL_VIRT_END = .);
    PROVIDE(__KERNEL_PHYS_END = . - __KERNEL_ADDR_TRNS);
    PROVIDE(__KERNEL_SIZE = __KERNEL_PHYS_END - __KERNEL_PHYS_LINK);
}