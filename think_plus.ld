OUTPUT_ARCH("riscv")
ENTRY(_entry)

MEMORY
{
    flash (rx)  : ORIGIN = 0x20010000, LENGTH = 512M - 0x10000
    dtim  (rwx) : ORIGIN = 0x80000000, LENGTH = 16K
}

SECTIONS
{
    .text : {
        *(.text.init)
        *(.text*)
        *(.rodata*)
    } > flash

    . = ALIGN(4);

    # data load from flash memory
    __data_load = .;

    .data : AT(__data_load) {
        __data_start = ABSOLUTE(.);
        *(.data*)
        *(.sdata*)
        __data_end = ABSOLUTE(.);
    } > dtim

    . = ALIGN(4);

    .bss (NOLOAD) : {
        __bss_start = ABSOLUTE(.);
        *(.bss*)
        *(.sbss*)
        *(COMMON)
        __bss_end = ABSOLUTE(.);
    } > dtim

    . = ALIGN(4);
}
