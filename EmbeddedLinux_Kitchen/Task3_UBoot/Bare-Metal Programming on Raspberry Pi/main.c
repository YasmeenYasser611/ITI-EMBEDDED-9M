#define GPIO_BASE 0x3F200000 // Base address for GPIO
#define GPFSEL0   (GPIO_BASE + 0x00) // GPIO Function Select 0
#define GPSET0    (GPIO_BASE + 0x1C) // GPIO Pin Output Set 0
#define GPCLR0    (GPIO_BASE + 0x28) // GPIO Pin Output Clear 0

void main(void) {
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
