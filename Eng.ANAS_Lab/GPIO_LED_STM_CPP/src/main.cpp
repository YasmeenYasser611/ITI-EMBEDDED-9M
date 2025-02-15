#include "LED.hpp"

int main() 
{
    LED led(GPIO::GPIO_A, GPIO::PIN5);
    LED led2(GPIO::GPIO_B, GPIO::PIN0);
    
    // Turn the LED on
    led.turnOn();
    led2.turnOn();
    while (1) 
    {
        // Toggle LED every second 
        led.toggle();
        led2.toggle();
        for (volatile int i = 0; i < 1000000; i++); // delay for second 
    }
    
    return 0;
}

