#ifndef GPIO_PRIVATE_H
#define GPIO_PRIVATE_H

#include"STD_TYPES.h"


#define GPIO_PORT(port) ((GPIO_Reg_t *)(0x40020000U + ((port) * 0x400U)))


typedef struct
{
    uint32_t MODER;     // 0x00: GPIO port mode register
    uint32_t OTYPER;    // 0x04: GPIO port output type register
    uint32_t OSPEEDR;   // 0x08: GPIO port output speed register
    uint32_t PUPDR;     // 0x0C: GPIO port pull-up/pull-down register
    uint32_t IDR;       // 0x10: GPIO port input data register
    uint32_t ODR;       // 0x14: GPIO port output data register
    uint32_t BSRR;      // 0x18: GPIO port bit set/reset register
    uint32_t LCKR;      // 0x1C: GPIO port configuration lock register
    uint32_t AFRL;      // 0x20: GPIO alternate function low register
    uint32_t AFRH;      // 0x24: GPIO alternate function high register
} GPIO_Reg_t;



#endif