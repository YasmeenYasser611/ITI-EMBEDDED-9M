
#include "GPIO.hpp"
#include "GPIO_Private.h"

GPIO::GPIO(Port port, Pin pin) : port(port), pin(pin) 
{

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
