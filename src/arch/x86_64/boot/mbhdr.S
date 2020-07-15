.code32

.section .multiboot, "awdx"

.balign 4
multiboot_header:
    .4byte 0xE85250D6                 # magic
    .4byte 0x0                        # architecture 0 (protected mode i386)
    .4byte multiboot_header_end - multiboot_header  # multiboot_header length

    .4byte 0x100000000 - (0xE85250D6 + 0x0 + (multiboot_header_end - multiboot_header)) # checksum

    .2byte 0x0  # type
    .2byte 0x0  # flags
    .4byte 0x8  # size
multiboot_header_end:
