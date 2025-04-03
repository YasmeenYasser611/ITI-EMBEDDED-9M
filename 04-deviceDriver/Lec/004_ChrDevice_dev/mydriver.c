#include <linux/module.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/device.h>

static ssize_t read_callback(struct file *, char __user *, size_t, loff_t *);
static ssize_t write_callback(struct file *, const char __user *, size_t, loff_t *);

dev_t _device_number = 0;
struct cdev _cdev;

struct file_operations _fops = 
{
    .read = read_callback,
    .write = write_callback
};

struct class *_class;
struct device *_device;

static ssize_t read_callback(struct file *file, char __user *user, size_t size, loff_t *off)
{
    return size;
}

static ssize_t write_callback(struct file *file, const char __user *user, size_t size, loff_t *off)
{
    return size;
}

static __init int mykernel_init(void)
{
    int ret = 0;
    int err;

    printk("Hello from kernel init\n");

    ret = alloc_chrdev_region(&_device_number, 2, 1, "device");
    if (ret < 0)
    {
        printk("Error in allocation\n");
        // goto unreg;
        return ret;
        
    }

    cdev_init(&_cdev, &_fops);

    err = cdev_add(&_cdev, _device_number, 1);
    if (err < 0)
    {
        printk("Error in cdev_add\n"); 
        // goto unreg;
        return err;
        
    }

    _class = class_create("myclass");
    _device = device_create(_class, NULL, _device_number, NULL, "mydevice");

    printk("major: %d, minor: %d\n", MAJOR(_device_number), MINOR(_device_number));

    return 0;
}

static __exit void mykernel_exit(void)
{
    printk("Hello from kernel exit\n");
    
    device_destroy(_class, _device_number);
    class_destroy(_class);
    cdev_del(&_cdev);
    unregister_chrdev_region(_device_number, 1);

    printk("Bye Kernel \n");
}

module_init(mykernel_init);
module_exit(mykernel_exit);

MODULE_LICENSE("GPL");
