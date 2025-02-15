#ifndef LED_HPP
#define LED_HPP

#include "GPIO.hpp"
#include"STD_TYPES.h"

class LED : public GPIO 
{
private:
    Value currentState;
    void enableRCC(); // Function to manually enable RCC for the port
    
public:
    LED(Port port, Pin pin);  // Constructor

    void init();    // Initialize LED (Enable RCC and set pin mode)
    void turnOn();  // Turns the LED on
    void turnOff(); // Turns the LED off
    void toggle();  // Toggles LED state


};

#endif // LED_HPP
