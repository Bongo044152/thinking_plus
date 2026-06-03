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

    .bss : {
        *(.bss*)
        *(COMMON)
    } > dtim
    
    . = ALIGN(4);

    .data : {
        *(.data*)
    } > dtim

    . = ALIGN(4);
}
