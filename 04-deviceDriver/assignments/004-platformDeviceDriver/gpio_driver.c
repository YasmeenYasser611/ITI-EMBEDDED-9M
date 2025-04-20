#include <linux/module.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/io.h>
#include <linux/mod_devicetable.h>
#include "device.h"

#define NO_ENTRIES 2
#define GPIO_BASE  0x3F200000
#define GPFSEL0    0x00
#define GPSET0     0x1C
#define GPCLR0     0x28
#define GPIO_SIZE  0xB4
#define LED_PIN_1  2
#define LED_PIN_2  3

/* File operations */
static ssize_t read_callback(struct file *, char __user *, size_t, loff_t *);
static ssize_t write_callback(struct file *, const char __user *, size_t, loff_t *);
static int open_callback(struct inode *, struct file *);

static const struct file_operations _fops = {
    .owner = THIS_MODULE,  // THIS IS CRUCIAL
    .open = open_callback,
    .read = read_callback,
    .write = write_callback,
};

struct prv_data_driver {
    dev_t device_number;
    struct class* _class;
    void __iomem *gpio_base;
};

struct prv_data_device {
    struct cdev _cdev;
    struct device* _device;
    struct gpio gpio;
    int led_pin;
};

static struct prv_data_driver _prvtDrvData;

static const struct platform_device_id _id_table[] = {
    { "led1", 0 },
    { "led2", 1 },
    { }
};
MODULE_DEVICE_TABLE(platform, _id_table);

/* File operation implementations */
int open_callback(struct inode *inode, struct file *file) {
    struct prv_data_device *dev_data = container_of(inode->i_cdev, struct prv_data_device, _cdev);
    file->private_data = dev_data;
    
    printk("Opened LED device (pin %d)\n", dev_data->led_pin);
    return 0;
}

static ssize_t read_callback(struct file *file, char __user *user, size_t size, loff_t *offst) {
    struct prv_data_device *dev_data = file->private_data;
    u32 reg_value = ioread32(dev_data->gpio.gpset);
    int gpio_state = (reg_value >> dev_data->led_pin) & 1;
    printk("GPIO%d state: %d\n", dev_data->led_pin, gpio_state);
    return 0;
}
static ssize_t write_callback(struct file *file, const char __user *user, 
                            size_t size, loff_t *offst) 
{
    struct prv_data_device *dev_data = file->private_data;
    char buff[10] = {0};
    int ret = 0;
    
    printk(KERN_INFO "Write callback entered for GPIO%d\n", dev_data->led_pin);
    
    if (!dev_data) {
        printk(KERN_ERR "No private data!\n");
        return -EFAULT;
    }

    if (size == 0 || size > sizeof(buff) - 1)
        size = sizeof(buff) - 1;

    if (copy_from_user(buff, user, size)) {
        printk(KERN_ERR "Failed to copy from user\n");
        return -EFAULT;
    }

    printk(KERN_INFO "Command received: %c for GPIO%d\n", buff[0], dev_data->led_pin);
    
    if (buff[0] == '1') {
        printk(KERN_INFO "Setting GPIO%d\n", dev_data->led_pin);
        iowrite32(1 << dev_data->led_pin, dev_data->gpio.gpset);
    } else if (buff[0] == '0') {
        printk(KERN_INFO "Clearing GPIO%d\n", dev_data->led_pin);
        iowrite32(1 << dev_data->led_pin, dev_data->gpio.gpclr);
    } else {
        printk(KERN_WARNING "Invalid command: %c\n", buff[0]);
        ret = -EINVAL;
    }

    return ret ? ret : size;
}

static int probeCbf(struct platform_device *pdev)
{
    struct prv_data_device *dev_data;
    unsigned int current_value;
    int ret;
    
    dev_data = devm_kzalloc(&pdev->dev, sizeof(*dev_data), GFP_KERNEL);
    if (!dev_data)
        return -ENOMEM;
    
    /* Setup GPIO registers */
    dev_data->gpio.gpset = _prvtDrvData.gpio_base + GPSET0;
    dev_data->gpio.gpclr = _prvtDrvData.gpio_base + GPCLR0;
    dev_data->gpio.gpfsels = _prvtDrvData.gpio_base + GPFSEL0;
    
    /* Configure GPIO pin */
    dev_data->led_pin = (pdev->id == 0) ? LED_PIN_1 : LED_PIN_2;
    
    /* Set GPIO function to output */
    current_value = ioread32(dev_data->gpio.gpfsels);
    printk("Current GPFSEL0 value: 0x%08x\n", current_value);
    
    current_value &= ~(7 << (dev_data->led_pin * 3));
    current_value |= (1 << (dev_data->led_pin * 3));
    
    printk("Setting GPFSEL0 to: 0x%08x (pin %d)\n", current_value, dev_data->led_pin);
    iowrite32(current_value, dev_data->gpio.gpfsels);
    
    /* Verify write */
    printk("New GPFSEL0 value: 0x%08x\n", ioread32(dev_data->gpio.gpfsels));
    
    /* Character device setup */
    cdev_init(&dev_data->_cdev, &_fops);
    ret = cdev_add(&dev_data->_cdev, _prvtDrvData.device_number + pdev->id, 1);
    if (ret) {
        dev_err(&pdev->dev, "Failed to add cdev\n");
        return ret;
    }
    
    dev_data->_device = device_create(_prvtDrvData._class, NULL,
                                    _prvtDrvData.device_number + pdev->id,
                                    dev_data, "mydevice-%d", pdev->id + 1);
    if (IS_ERR(dev_data->_device)) {
        ret = PTR_ERR(dev_data->_device);
        cdev_del(&dev_data->_cdev);
        return ret;
    }
    
    platform_set_drvdata(pdev, dev_data);
    dev_info(&pdev->dev, "Probed GPIO%d\n", dev_data->led_pin);
    return 0;
}

static int removeCbf(struct platform_device *pdev)
{
    struct prv_data_device *dev_data = platform_get_drvdata(pdev);
    
    device_destroy(_prvtDrvData._class, _prvtDrvData.device_number + pdev->id);
    cdev_del(&dev_data->_cdev);
    dev_info(&pdev->dev, "Removed GPIO%d\n", dev_data->led_pin);
    return 0;
}

static struct platform_driver _platDriver = {
    .probe = probeCbf,
    .remove = removeCbf,
    .id_table = _id_table,
    .driver = {
        .name = "led_gpio",
        .owner = THIS_MODULE,
    }
};

static int __init mykernel_init(void)
{
    int ret;
    
    ret = alloc_chrdev_region(&_prvtDrvData.device_number, 0, NO_ENTRIES, "led_device");
    if (ret)
        return ret;
    
    _prvtDrvData._class = class_create(THIS_MODULE, "led_driver");
    if (IS_ERR(_prvtDrvData._class)) {
        ret = PTR_ERR(_prvtDrvData._class);
        unregister_chrdev_region(_prvtDrvData.device_number, NO_ENTRIES);
        return ret;
    }
    
    _prvtDrvData.gpio_base = ioremap(GPIO_BASE, GPIO_SIZE);
    if (!_prvtDrvData.gpio_base) {
        class_destroy(_prvtDrvData._class);
        unregister_chrdev_region(_prvtDrvData.device_number, NO_ENTRIES);
        return -ENOMEM;
    }
    
    ret = platform_driver_register(&_platDriver);
    if (ret) {
        iounmap(_prvtDrvData.gpio_base);
        class_destroy(_prvtDrvData._class);
        unregister_chrdev_region(_prvtDrvData.device_number, NO_ENTRIES);
    }
    
    return ret;
}

static void __exit mykernel_exit(void)
{
    platform_driver_unregister(&_platDriver);
    iounmap(_prvtDrvData.gpio_base);
    class_destroy(_prvtDrvData._class);
    unregister_chrdev_region(_prvtDrvData.device_number, NO_ENTRIES);
}

module_init(mykernel_init);
module_exit(mykernel_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Yasmeen");
MODULE_DESCRIPTION("LED Control Platform Driver");