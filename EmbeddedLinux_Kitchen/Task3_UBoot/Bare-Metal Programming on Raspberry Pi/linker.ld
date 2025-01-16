/* Minimal Linker Script for Bare-Metal ARM on BCM2837 */
ENTRY(_start) /* Set entry point to `_start` */

SECTIONS {
    /* Place everything at the start of DRAM */
    . = 0x00080000;

    .text : {
        *(.text*)   /* All `.text` sections */
        *(.rodata*) /* All `.rodata` sections */
    }
    .data : { *(.data*) }
     . = ALIGN(4);
     _bss_start = .;
     .bss : { *(.bss* COMMON) }
     . = ALIGN(4);
     _bss_end = .;

 
}
