#include <linux/module.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/io.h>

#define NO_DEVICES 2U
#define GPIO_BASE  0x3F200000  // Base address for GPIO (Raspberry Pi 3)
#define GPFSEL0    0x00        // GPIO Function Select 0
#define GPSET0     0x1C        // GPIO Pin Output Set 0
#define GPCLR0     0x28        // GPIO Pin Output Clear 0
#define GPIO_SIZE  0xB4        // Size to map all registers

#define LED_PIN_1  2  // GPIO2
#define LED_PIN_2  3  // GPIO3

/***** Code Section *****/
static ssize_t read_callback(struct file *, char __user *, size_t, loff_t *);
static ssize_t write_callback(struct file *, const char __user *, size_t, loff_t *);
int open_callback(struct inode *, struct file *);

const struct file_operations _fops = {
    .open = open_callback,
    .read = read_callback,
    .write = write_callback,
};

/* Device resources */
struct gpio {
    void __iomem *gpset;  // GPIO Pin Output Set Register
    void __iomem *gpclr;  // GPIO Pin Output Clear Register
    void __iomem *gpfsels; // GPIO Function Select Registers
};

struct prvt_device_resource {
    struct gpio gpio;
    int perm;
    struct cdev _cdev;
    struct device* _device;
};

/* To create character device driver */
struct prvt_driver_data {
    dev_t _device_number;
    struct class* _class;
    int numberOfDevices;
    struct prvt_device_resource _device_resource[NO_DEVICES];
};

/* Object */
static void __iomem *gpio_base = NULL;

#define GPIO2_ADDR (GPIO_BASE + GPSET0)
#define GPIO3_ADDR (GPIO_BASE + GPSET0)
#define GPIO2_GPFSEL (GPIO_BASE + GPFSEL0)
#define GPIO3_GPFSEL (GPIO_BASE + GPFSEL0)

struct prvt_driver_data _driver_data = {
    .numberOfDevices = NO_DEVICES,
    ._device_resource = {
        [0] = { 
            .gpio = { 
                .gpset = (void __iomem *)GPIO2_ADDR,  // Direct address for GPIO2
                .gpclr = (void __iomem *)GPIO2_ADDR,  // Direct address for GPIO2
                .gpfsels = (void __iomem *)GPIO2_GPFSEL  // Direct address for GPIO2
            },
            .perm = 1  // Device 1 (GPIO2)
        }, 
        [1] = { 
            .gpio = { 
                .gpset = (void __iomem *)GPIO3_ADDR,  // Direct address for GPIO3
                .gpclr = (void __iomem *)GPIO3_ADDR,  // Direct address for GPIO3
                .gpfsels = (void __iomem *)GPIO3_GPFSEL  // Direct address for GPIO3
            },
            .perm = 2  // Device 2 (GPIO3)
        }
    }
};

int open_callback(struct inode *inode, struct file *file) {
    int minor = MINOR(inode->i_rdev);
    struct prvt_device_resource *lc_dev_res;
    
    lc_dev_res = container_of(inode->i_cdev, struct prvt_device_resource, _cdev);
    
    
    file->private_data = lc_dev_res;

    printk("my uid: %d\n", inode->i_uid.val);
    printk("my gid: %d\n", inode->i_gid.val);
    printk("my minor is: %d\n", minor);
    return 0;
}

static ssize_t read_callback(struct file *file, char __user *user, size_t size, loff_t *offst) {
    struct prvt_device_resource *private = (struct prvt_device_resource *)file->private_data;
    printk("shared read\n");

    int gpio2_state = ioread32(private->gpio.gpset);
    printk("GPIO2 state: %d\n", gpio2_state);

    return 0;
}

static ssize_t write_callback(struct file *file, const char __user *user, size_t size, loff_t *offst) {
    struct prvt_device_resource *private = (struct prvt_device_resource *)file->private_data;
    char buff[10] = {0};  // Increased buffer size for safety
    if (size > sizeof(buff) - 1)
        size = sizeof(buff) - 1;

    if (copy_from_user(buff, user, size))
        return -EFAULT;

    printk("Writing value: %d\n", buff[0]);

    // Control GPIO based on the value received (1: turn on, 0: turn off)
    if (private->perm == 1) {  // If it's Device 1 (GPIO2)
        if (buff[0] == '1') {
            printk("GPIO %d Turned ON\n", LED_PIN_1);
            iowrite32(1 << LED_PIN_1, private->gpio.gpset); // Set GPIO2
        } else {
            printk("GPIO %d Turned OFF\n", LED_PIN_1);
            iowrite32(1 << LED_PIN_1, private->gpio.gpclr); // Clear GPIO2
        }
    } else if (private->perm == 2) {  // If it's Device 2 (GPIO3)
        if (buff[0] == '1') {
            printk("GPIO %d Turned ON\n", LED_PIN_2);
            iowrite32(1 << LED_PIN_2, private->gpio.gpset); // Set GPIO3
        } else {
            printk("GPIO %d Turned OFF\n", LED_PIN_2);
            iowrite32(1 << LED_PIN_2, private->gpio.gpclr); // Clear GPIO3
        }
    }

    return size;
}

static __init int mykernel_init(void) {
    int i = 0;
    unsigned int current_value;
    printk("Hello from kernel\n");

    alloc_chrdev_region(&_driver_data._device_number, 0, NO_DEVICES, "device");
    _driver_data._class = class_create(THIS_MODULE, "itiDriver");

    gpio_base = ioremap(GPIO_BASE, GPIO_SIZE);
    if (!gpio_base) {
        printk("Failed to map GPIO registers\n");
        return -ENOMEM;
    }

    for (i = 0; i < NO_DEVICES; i++) {
        _driver_data._device_resource[i].gpio.gpset = gpio_base + GPSET0;
        _driver_data._device_resource[i].gpio.gpclr = gpio_base + GPCLR0;

        if (i == 0) {
            _driver_data._device_resource[i].gpio.gpfsels = gpio_base + GPFSEL0;
            current_value = ioread32(_driver_data._device_resource[i].gpio.gpfsels);
            current_value &= ~(7 << (LED_PIN_1 * 3));  // Clear the bits for GPIO2
            iowrite32(current_value, _driver_data._device_resource[i].gpio.gpfsels);
            current_value |= (1 << (LED_PIN_1 * 3));  // Set GPIO2 as output
            iowrite32(current_value, _driver_data._device_resource[i].gpio.gpfsels);
        } else {
            _driver_data._device_resource[i].gpio.gpfsels = gpio_base + GPFSEL0;
            current_value = ioread32(_driver_data._device_resource[i].gpio.gpfsels);
            current_value &= ~(7 << (LED_PIN_2 * 3));  // Clear the bits for GPIO3
            iowrite32(current_value, _driver_data._device_resource[i].gpio.gpfsels);
            current_value |= (1 << (LED_PIN_2 * 3));  // Set GPIO3 as output
            iowrite32(current_value, _driver_data._device_resource[i].gpio.gpfsels);
        }

        cdev_init(&_driver_data._device_resource[i]._cdev, &_fops);
        cdev_add(&_driver_data._device_resource[i]._cdev, _driver_data._device_number + i, 1);
        device_create(_driver_data._class, NULL, _driver_data._device_number + i, NULL, "mydevice-%d", i + 1);
    }

    printk("major: %d , minor: %d\n", MAJOR(_driver_data._device_number), MINOR(_driver_data._device_number));
    return 0;
}

static __exit void mykernel_exit(void) {
    int i = 0;

    for (i = 0; i < NO_DEVICES; i++) {
        cdev_del(&_driver_data._device_resource[i]._cdev);
        device_destroy(_driver_data._class, _driver_data._device_number + i);
    }
    class_destroy(_driver_data._class);
    unregister_chrdev_region(_driver_data._device_number, NO_DEVICES);
    iounmap(gpio_base);
    printk("Bye from kernel\n");
}

module_init(mykernel_init);
module_exit(mykernel_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Yasmeen");
MODULE_DESCRIPTION("LED Control Driver");
