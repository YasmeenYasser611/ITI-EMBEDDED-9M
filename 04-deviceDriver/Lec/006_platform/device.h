#ifndef DEVICE_PRIVATE
#define DEVICE_PRIVATE


struct platform_private_device {
    struct cdev  _cdev;
    struct device _device;
};

struct gpio {
    void __iomem *gpset;  // GPIO Pin Output Set Register
    void __iomem *gpclr;  // GPIO Pin Output Clear Register
    void __iomem *gpfsels; // GPIO Function Select Registers
    int buffSize;
    int perm;
    int mode;
    void* allocatedMemory;
};

#endif