
#include "GPIO.hpp"
#include "GPIO_Private.h"

GPIO::GPIO() : port(INVALID_PORT), pin(INVALID_PIN) 
{
    //Invalid GPIO configuration! Use parameterized constructor.
    //port=-1
    //pin=-1
}

GPIO::GPIO(Port port, Pin pin) : port(port), pin(pin) 
{
     // Valid GPIO initialization
}

void GPIO::setMode(Mode mode) 
{
    GPIO_Reg_t* reg = GPIO_PORT(port);
    reg->MODER &= ~(0x3U << (pin * 2));
    reg->MODER |= (mode << (pin * 2));
}


void GPIO::write(Value value) 
{
    GPIO_Reg_t* reg = GPIO_PORT(port);
    if (value == HIGH) {
        reg->BSRR = (1U << pin);
    } else {
        reg->BSRR = (1U << (pin + 16));
    }
}
