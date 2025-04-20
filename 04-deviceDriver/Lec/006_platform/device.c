#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/cdev.h>
#include "device.h"

#define GPIO_BASE  0x3F200000  // Base address for GPIO (Raspberry Pi 3)
#define GPFSEL0    0x00        // GPIO Function Select 0
#define GPSET0     0x1C        // GPIO Pin Output Set 0
#define GPCLR0     0x28        // GPIO Pin Output Clear 0
#define GPIO_SIZE  0xB4        // Size to map all registers

#define GPIO_DIO    1
#define GPIO_UART   5

struct gpio _gpio[2] = {
    [0] = {
        .buffSize = 50,
        .perm = 0x01U,
        .gpfsels = (void __iomem *)GPIO_BASE + GPFSEL0,
        .gpset = (void __iomem *)GPIO_BASE + GPSET0,
        .gpclr = (void __iomem *)GPIO_BASE + GPCLR0,
        .mode = GPIO_DIO
    },
    [1] = {
        .buffSize = 100,
        .perm = 0x02U,
        .gpfsels = (void __iomem *)(GPIO_BASE + GPIO_SIZE + GPFSEL0),
        .gpset = (void __iomem *)GPIO_BASE + GPIO_SIZE + GPSET0,
        .gpclr = (void __iomem *)GPIO_BASE + GPIO_SIZE + GPCLR0,
        .mode = GPIO_UART
    }
};

struct platform_private_device __platDevicePrivate[2];

void releaseCbf (struct device *dev);

struct platform_device _platDevice[2] = {
    [0] = {
    .name = "ahmed",
    .id = 0,
    .dev = {
        .driver_data = (struct gpio*)_gpio,
        .platform_data = (struct platform_private_device*)&__platDevicePrivate,
        .release = releaseCbf,
        },
    },
    [1] = {
        .name = "fady",
        .id = 1,
        .dev = {
            .platform_data = (struct platform_private_device*)&__platDevicePrivate[1],
            .driver_data = (struct gpio*)(_gpio+1),
            .release = releaseCbf,
        }
    }
};

void releaseCbf (struct device *dev){

}

static __init int mykernel_init(void) {
    platform_device_register(&_platDevice[0]);
    platform_device_register(&_platDevice[1]);    
    return 0;
}

static __exit void mykernel_exit(void) {
    platform_device_unregister(&_platDevice[0]);
    platform_device_unregister(&_platDevice[1]);
}

module_init(mykernel_init);
module_exit(mykernel_exit);

MODULE_LICENSE("GPL");