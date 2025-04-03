#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>

/* Function prototypes */
ssize_t my_write(struct file *, const char __user *, size_t, loff_t *);

/* Global variables */
static dev_t _dev;
static struct cdev _cdev;
static struct class *_class;
static struct device *_device;

/* File operations structure */
static const struct file_operations _fops = {
    .owner = THIS_MODULE,
    .write = my_write,
};

/* Write function */
ssize_t my_write(struct file *flip, const char __user *user, size_t size, loff_t *offst)
{
    printk(KERN_INFO "Write operation called\n");
    return size;
}

/* Module initialization */
static __init int my_driver_init(void)
{
    int status;

    /* Allocate device number */
    status = alloc_chrdev_region(&_dev, 0, 1, "mydevice");
    if (status < 0) {
        printk(KERN_ERR "Failed to allocate device number\n");
        return status;
    }

    /* Initialize character device */
    cdev_init(&_cdev, &_fops);
    status = cdev_add(&_cdev, _dev, 1);
    if (status < 0) {
        printk(KERN_ERR "Failed to add cdev\n");
        unregister_chrdev_region(_dev, 1);
        return status;
    }

    /* Create device class (Fixed) */
    _class = class_create("mydevice_class");
    if (IS_ERR(_class)) {
        printk(KERN_ERR "Failed to create class\n");
        cdev_del(&_cdev);
        unregister_chrdev_region(_dev, 1);
        return PTR_ERR(_class);
    }

    /* Create device node */
    _device = device_create(_class, NULL, _dev, NULL, "mydevice");
    if (IS_ERR(_device)) {
        printk(KERN_ERR "Failed to create device\n");
        class_destroy(_class);
        cdev_del(&_cdev);
        unregister_chrdev_region(_dev, 1);
        return PTR_ERR(_device);
    }

    printk(KERN_INFO "Device initialized: major %d, minor %d\n", MAJOR(_dev), MINOR(_dev));
    return 0;
}

/* Module exit */
static __exit void my_driver_exit(void)
{
    device_destroy(_class, _dev);
    class_destroy(_class);
    cdev_del(&_cdev);
    unregister_chrdev_region(_dev, 1);
    printk(KERN_INFO "Device removed\n");
}

module_init(my_driver_init);
module_exit(my_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Yasmeen");
MODULE_DESCRIPTION("Simple Character Device Driver with class_create");
