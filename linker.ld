OUTPUT_FORMAT("elf32-i386")
ENTRY(_start)

SECTIONS
{
    _start = 0x1000;
    . = 0x1000;
	.multiboot_header : {
        *(.multiboot_header)
    } > RAM

    .text : {
        *(.text)
        *(.text.*)
    } > RAM

    .data : {
        *(.data)
        *(.data.*)
    } > RAM

    .bss : {
        *(.bss)
        *(COMMON)
    } > RAM
}

