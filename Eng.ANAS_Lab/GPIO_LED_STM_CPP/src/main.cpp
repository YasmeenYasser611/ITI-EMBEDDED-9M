#include "LED.hpp"

void delay() {
    for (volatile int i = 0; i < 1000000; i++); // Simple delay for 1 second 
}

int main() 
{

    LED red(GPIO::GPIO_A, GPIO::PIN5);   // Red LED on PA5
    LED yellow(GPIO::GPIO_A, GPIO::PIN6); // Yellow LED on PA6
    LED green(GPIO::GPIO_A, GPIO::PIN7);  // Green LED on PA7
    while (1) 
    {
        // Red Light (Stop)
        red.turnOn();
        yellow.turnOff();
        green.turnOff();
        delay();

        // Yellow Light (Get Ready)
        red.turnOff();
        yellow.turnOn();
        green.turnOff();
        delay();

        // Green Light (Go)
        red.turnOff();
        yellow.turnOff();
        green.turnOn();
        delay();
    }

    return 0;
}
