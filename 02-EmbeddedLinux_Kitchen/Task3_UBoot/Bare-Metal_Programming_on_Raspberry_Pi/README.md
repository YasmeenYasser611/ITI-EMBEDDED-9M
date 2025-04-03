# Yasmeen Yasser Mohamed
## EmbeddedLinuxKitchen Task 3: U-Boot and Bare-Metal Programming on Raspberry Pi 😊

### **Objective**
To turn on an LED on the Raspberry Pi without using a kernel, by directly manipulating the GPIO registers. This involves:
1. Writing bare-metal C code to access GPIO hardware.
2. Creating a linker script to load the program at a specified memory address.
3. Using U-Boot to load and execute the program in DRAM.

---

### **Challenges**

#### 1. **Directly Accessing GPIO Registers**
- When working without a kernel, you must handle hardware by directly accessing memory-mapped registers.
- For the Raspberry Pi’s BCM2837 (Raspberry Pi 3B+), you need to:
  - Locate the base address of the GPIO controller.
  - Configure the correct GPIO pin as an output.
  - Set the appropriate pin high to turn on the LED.



```c
#define GPIO_BASE 0x3F200000 // Base address for GPIO
#define GPFSEL0   (GPIO_BASE + 0x00) // GPIO Function Select 0
#define GPSET0    (GPIO_BASE + 0x1C) // GPIO Pin Output Set 0
#define GPCLR0    (GPIO_BASE + 0x28) // GPIO Pin Output Clear 0

void main(void) 
{
    volatile unsigned int *gpfsel0 = (unsigned int *)GPFSEL0;
    volatile unsigned int *gpset0 = (unsigned int *)GPSET0;

    // Configure GPIO2 as output
    *gpfsel0 &= ~(0b111 << 6); // Clear bits 6-8 (GPIO2),GPIO2 is controlled by bits 6-8 in GPFSEL0
    *gpfsel0 |= (0b001 << 6);  // Set bits 6-8 to 001 (output mode) , GPIO2 is controlled by bit 2 in GPSET0.

    // Set GPIO2 HIGH to turn the LED ON
    *gpset0 = (1 << 2);        // Set bit 2 in GPSET0 (GPIO2)

    // Infinite loop to keep the LED on
    while (1) {
        // Do nothing
    }
}
```

#### 2. **Linker Script Implementation**
- The program must be loaded at a specific memory address in DRAM.
- Avoid using the very first address of DRAM (0x00000000) because it may interfere with U-Boot.
- A linker script is required to correctly position the `.text`, `.data`, and `.bss` sections in memory.

```c
/* Minimal Linker Script for Bare-Metal ARM on BCM2837 */
ENTRY(_start) /* Set entry point to `_start` */

SECTIONS {
    /*  do not Place everything at the start of DRAM */
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

```



#### 3. **start up code  Implementation**

```c
.global _start
.global main

.section .text
_start:
    
    /* Jump to main() */
    bl main

    /* Hang if main() returns */
hang:
    b hang

```

#### 4. **Compilation Commands**
- Compile the startup code into an object file.

    `aarch64-linux-gnu-gcc -Wall -O2 -ffreestanding -nostdinc -nostdlib -nostartfiles start.S -o start.o -c `

- Compile the C code into an object file.

    `aarch64-linux-gnu-gcc -Wall -O2 -ffreestanding -nostdinc -nostdlib -nostartfiles main.c  -o main.o -c`

- Link the object file with the linker script
    `aarch64-linux-gnu-ld -nostdlib  start.o main.o -T linker.ld  -o test.elf`

- Convert the ELF file to a binary file
   ` aarch64-linux-gnu-objcopy -O binary test.elf test.img`



![](1.png "")



- sd card contents now:

![](2.png "")

#### 5. **Using U-Boot to Load and Run the Program**
- U-Boot is used to load the binary into memory and execute it.

    * sudo minicom -s /dev/ttyUSB0
    * fatload mmc 0:1 0x00080000 test.img 
    * go 0x00080000  

    * and the led on GPIO2 = pin3 with turn on 

![](3.png "")

![](4.jpeg "")









