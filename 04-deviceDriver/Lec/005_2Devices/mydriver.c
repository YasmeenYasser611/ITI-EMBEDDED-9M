/*****Header Section******/

#include <linux/module.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/device.h>

#define NO_DEVICES 2U
#define WRONLY     1U
#define RRONLY     2U

/*****Code Section******/

static ssize_t read_callback(struct file *, char __user *, size_t, loff_t *);
static ssize_t write_callback(struct file *, const char __user *, size_t, loff_t *);
int open_callback (struct inode *, struct file *);

const struct file_operations _fops = {
    .open = open_callback,
    .read = read_callback,
    .write = write_callback,
};
/*device resources*/
struct gpio {
    int DR;
    int DDR;
};
struct prvt_device_resource {
    struct gpio* gpio;
    int perm;
    struct cdev _cdev;
};
/********/

/*to create character device driver*/
struct prvt_driver_data {
    /*will be allocated by the function provided by the kernel header*/
    dev_t _device_number;
    struct class* _class;
    struct device* _device;
    /******************/
    int numberOfDevices;
    struct prvt_device_resource _device_resource[NO_DEVICES];
};


/*OBJECT*/
struct prvt_driver_data _driver_data = {
    .numberOfDevices = NO_DEVICES,
    ._device_resource = {
        [0] = {
            .gpio = (struct gpio*)0x80,
            .perm = WRONLY,
            },
        [1] = {
            .gpio = (struct gpio*)0x88,
            .perm = RRONLY,
        },
    }
};
/*************/


int open_callback (struct inode *inode, struct file *file){
    int minor = 0;
    struct prvt_device_resource* lc_dev_res;
    minor = MINOR(inode->i_rdev);

    lc_dev_res = container_of(inode->i_cdev, struct prvt_device_resource, _cdev);


    /*assign the memory field to look at it's own resource [device]*/
    file->private_data = (struct prvt_device_resource*)lc_dev_res;

    printk("my uid: %d\n", inode->i_uid.val);
    printk("my gid: %d\n", inode->i_gid.val);

    printk("my minor is: %d\n", minor);
    return 0;
}

static ssize_t read_callback(struct file *file, char __user *user, size_t size, loff_t *offst)
{
    printk("shared read\n");
    return 0;
}
/*device 1*/
static ssize_t write_callback(struct file *file, const char __user *user, size_t size, loff_t *offst)
{
    // int buff[2];
    // copy_from_user(buff, user, size); 
    struct prvt_device_resource* private = (struct prvt_device_resource *)file->private_data;
    printk("hello from which device: %d\n", private->perm);

    printk("hello from write\n");
    return size;
}


/*Init Function*/
static __init int mykernel_init(void)
{
    int i = 0;
    /*print functio for kernel (dmesg)*/
    printk("Hello from kernel\n");
    /*to allocate 2 devices*/
    alloc_chrdev_region(&_driver_data._device_number, 0, NO_DEVICES, "device");
    _driver_data._class = class_create("itiDriver");
 
    for(i = 0; i < NO_DEVICES; i++)
    {
        cdev_init(&_driver_data._device_resource[i]._cdev, &_fops);
        cdev_add(&_driver_data._device_resource[i]._cdev, _driver_data._device_number+i, 1);
        device_create(_driver_data._class, NULL, _driver_data._device_number+i, NULL, "mydevice-%d", i+1);
    }
    
    
    printk("major: %d , minor: %d\n", MAJOR(_driver_data._device_number), MINOR(_driver_data._device_number));
    /*init function succeeded*/
    return 0;
}


/*Deinit function*/
static __exit void mykernel_exit(void)
{
    int i = 0;
    for(i = 0; i < NO_DEVICES; i++)
    {
        cdev_del(&_driver_data._device_resource[i]._cdev);
        device_destroy(_driver_data._class, _driver_data._device_number+i);
    }

    class_destroy(_driver_data._class);
    unregister_chrdev_region(_driver_data._device_number, NO_DEVICES);
    printk("Bye Kernel \n");
}


module_init(mykernel_init);
module_exit(mykernel_exit);

MODULE_LICENSE("GPL");




/*
//BAD LOGIC USING 2 Write and 2 FIPS 
#include <linux/module.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/device.h>

#define NO_DEVICES 2

static ssize_t read_callback(struct file *, char __user *, size_t, loff_t *);
static ssize_t write_callback(struct file *, const char __user *, size_t, loff_t *);
static ssize_t write_callback_1(struct file *, const char __user *, size_t, loff_t *);

dev_t _device_number = 0;
struct cdev _cdev[NO_DEVICES];

struct file_operations _fops[NO_DEVICES] = {
    [0] = {
        .read = read_callback,
        .write = write_callback
    },
    [1] = {
        .read = read_callback,
        .write = write_callback_1
    }
};

struct class *_class;

struct gpio 
{
    int DR;
    int DDR;

};

static ssize_t read_callback(struct file *file, char __user *user, size_t size, loff_t *off)
{
    printk("Hello from shared read \n");
    return 0;
}

static ssize_t write_callback(struct file *file, const char __user *user, size_t size, loff_t *off)
{
    printk("Hello from write 1 \n");

    int buff[2];
    copy_from_user(buff , user , size);

    struct gpio* baseaddress = (struct gpio * ) 0x80;
    baseaddress->DR = buff[0]; //the entered value 1 or 0 
    baseaddress->DDR =1; //output
    
    return size;
}
static ssize_t write_callback_1(struct file *file, const char __user *user, size_t size, loff_t *off)
{
    printk("Hello from write 2\n");

    int buff[2];
    copy_from_user(buff , user , size);

    struct gpio* baseaddress = (struct gpio * ) 0x88;
    baseaddress->DR = buff[0];
    baseaddress->DDR =1;
    return size;
}

static __init int mykernel_init(void)
{

    int i=0;
    printk("Hello from kernel init\n");
    //to allocate 2 devices that 1 driver will controll them 

    alloc_chrdev_region(&_device_number, 0, NO_DEVICES, "device");
    _class = class_create("myclass");

    for(i = 0; i< NO_DEVICES ; i++)
    {
    cdev_init(&_cdev[i], &_fops[i]);
    cdev_add(&_cdev[i], _device_number + i, 1);
    device_create(_class, NULL, _device_number + i, NULL, "mydevice-%d" , i+1);
    }
    printk("major: %d, minor: %d\n", MAJOR(_device_number), MINOR(_device_number));
    return 0;
}

static __exit void mykernel_exit(void)
{
    int i =0 ;
    printk("Hello from kernel exit\n");
    
    for(i = 0; i< NO_DEVICES ; i++)
    {
    cdev_del(&_cdev[i]);
    device_destroy(_class, _device_number + i);
    }

    class_destroy(_class);
    unregister_chrdev_region(_device_number, NO_DEVICES);
    printk("Bye Kernel \n");
}

module_init(mykernel_init);
module_exit(mykernel_exit);

MODULE_LICENSE("GPL");

*/

