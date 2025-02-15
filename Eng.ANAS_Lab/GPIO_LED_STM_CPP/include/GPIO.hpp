#ifndef GPIO_HPP
#define GPIO_HPP

#include"STD_TYPES.h"

class GPIO {
public:
    enum Port {
        GPIO_A = 0,
        GPIO_B = 1,
        GPIO_C = 2,
        GPIO_D = 3,
        GPIO_E = 4,
        GPIO_H = 5
    };

    enum Pin {
        PIN0 = 0, 
        PIN1, 
        PIN2, 
        PIN3, 
        PIN4, 
        PIN5, 
        PIN6, 
        PIN7,
        PIN8, 
        PIN9, 
        PIN10, 
        PIN11, 
        PIN12, 
        PIN13, 
        PIN14, 
        PIN15
    };

    enum Mode {
        INPUT = 0x0,
        OUTPUT = 0x1,
 
    };



    enum Value {
        LOW = 0,
        HIGH = 1
    };

    GPIO(Port port, Pin pin);
    void setMode(Mode mode);
    void write(Value value);
   

protected:
    Port port;
    Pin pin;
};

#endif // GPIO_HPP