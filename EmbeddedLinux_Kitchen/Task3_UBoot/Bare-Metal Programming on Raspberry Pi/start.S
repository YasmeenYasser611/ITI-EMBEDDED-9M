.global _start
.global main

.section .text
_start:
    
    /* Jump to main() */
    bl main

    /* Hang if main() returns */
hang:
    b hang
