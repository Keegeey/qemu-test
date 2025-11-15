/* Linker script for TI LM3S6965 (Cortex-M3, similar to M4) */
MEMORY
{
    FLASH (rx)  : ORIGIN = 0x00000000, LENGTH = 256K
    SRAM (rwx)  : ORIGIN = 0x20000000, LENGTH = 64K
}

ENTRY(Reset_Handler)

SECTIONS
{
    .text :
    {
        KEEP(*(.isr_vector))
        *(.text*)
        *(.rodata*)
        . = ALIGN(4);
    } > FLASH

    .data :
    {
        _sdata = .;
        *(.data*)
        . = ALIGN(4);
        _edata = .;
    } > SRAM AT> FLASH

    _sidata = LOADADDR(.data);

    .bss :
    {
        _sbss = .;
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;
    } > SRAM

    _stack_top = ORIGIN(SRAM) + LENGTH(SRAM);
}
