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
        # data locate at dtim

        __data_start = .;
        *(.data*)
        *(.sdata*)
        __data_end = .;
    } > dtim

    . = ALIGN(4);

    .bss : {
        __bss_start = .;
        *(.bss*)
        *(COMMON)
        __bss_end = .;
    } > dtim

    . = ALIGN(4);
}
