#include "LED.hpp"


#define RCC_BASE   0x40023800
#define RCC_AHB1ENR (*((volatile uint32_t*)(RCC_BASE + 0x30))) // RCC AHB1 peripheral clock enable register


LED::LED() : GPIO(GPIO::INVALID_PORT, GPIO::INVALID_PIN) 
{
     
}

LED::LED(Port port, Pin pin) : GPIO(port, pin), currentState(LOW) 
{
    init(); // Call initialization function
}

void LED::init() {
    enableRCC();  // Enable RCC for the selected GPIO port
    setMode(OUTPUT); // Set pin as output
}

void LED::enableRCC() {
    // Enable RCC for the corresponding port
    switch(port) {
        case GPIO_A: RCC_AHB1ENR |= (1 << 0); break; // Enable GPIOA clock
        case GPIO_B: RCC_AHB1ENR |= (1 << 1); break; // Enable GPIOB clock
        case GPIO_C: RCC_AHB1ENR |= (1 << 2); break; // Enable GPIOC clock
        case GPIO_D: RCC_AHB1ENR |= (1 << 3); break; // Enable GPIOD clock
        case GPIO_E: RCC_AHB1ENR |= (1 << 4); break; // Enable GPIOE clock
        case GPIO_H: RCC_AHB1ENR |= (1 << 7); break; // Enable GPIOH clock
    }
}

void LED::turnOn() {
    write(HIGH);
    currentState = HIGH;
}

void LED::turnOff() {
    write(LOW);
    currentState = LOW;
}

void LED::toggle() {
    currentState = (currentState == HIGH) ? LOW : HIGH;
    write(currentState);
}
