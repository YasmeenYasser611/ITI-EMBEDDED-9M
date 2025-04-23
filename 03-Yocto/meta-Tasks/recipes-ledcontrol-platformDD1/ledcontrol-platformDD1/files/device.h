#ifndef DEVICE_H
#define DEVICE_H

#include <linux/io.h>

struct gpio 
{
    void __iomem *gpset;
    void __iomem *gpclr;
    void __iomem *gpfsels;
};

#endif