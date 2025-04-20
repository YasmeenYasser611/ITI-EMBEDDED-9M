#include <linux/module.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/mod_devicetable.h>
#include "device.h"
#include <linux/platfrom.h>

#define NO_ENTRIES 2


struct prv_data_device {
    struct cdev _cdev;
    struct device* _device;
};

struct prv_data_driver {
    dev_t device_number;
    struct class* _class;
    int numberInitEntries;
};

struct file_operations _fops ;

int probeCbf (struct platform_device *platResource);
int removeCbf (struct platform_device *platResource);

struct platform_device_id _id_table[2] = {
    [0] = {
        .name = "fady",
    },
    [1] = {
        .name = "ahmed"
    }
};

platform

struct prv_data_driver _prvtDrvData;
struct platform_driver _platDriver = {
    .probe = probeCbf,
    .remove = removeCbf,
    .id_table = _id_table,
    .driver = {
        .name = "_gpio",
    }
};

int probeCbf (struct platform_device *platResource)
{
    printk("device detected \n");
    struct gpio* _lc_gpio = (struct gpio*)platResource->dev.driver_data;
    struct platform_private_device* _lc_platDevice = platResource->dev.platform_data;



    cdev_init(&(_lc_platDevice->_cdev), &_fops);
    cdev_add(&(_lc_platDevice->_cdev), _prvtDrvData.device_number + platResource->id, 1);
    device_create(_prvtDrvData._class, NULL, _prvtDrvData.device_number + platResource->id, NULL, "mydevice-%d", platResource->id + 1);


    printk("hello my device %d\n", _lc_gpio->buffSize);  
    return 0;
}


int removeCbf (struct platform_device *platResource)
{
    printk("device removed \n");
    struct platform_private_device* _lc_platDevice = platResource->dev.platform_data;
    // struct gpio* _lc_gpio = (struct gpio*)platResource->dev.platform_data;
    // kfree(_lc_gpio->allocatedMemory);
    cdev_del(&_lc_platDevice->_cdev);
    device_destroy(_prvtDrvData._class, _prvtDrvData.device_number + platResource->id);
    return 0;
}

static __init int mykernel_init(void) {
    printk("hello from platform driver \n");
    alloc_chrdev_region(&_prvtDrvData.device_number, 0, NO_ENTRIES, "device");
    _prvtDrvData._class = class_create("mydriver");
    platform_driver_register(&_platDriver);
    return 0;
}

static __exit void mykernel_exit(void) {
    unregister_chrdev_region(_prvtDrvData.device_number, NO_ENTRIES);
    class_destroy(_prvtDrvData._class);
    platform_driver_unregister(&_platDriver);
}

module_init(mykernel_init);
module_exit(mykernel_exit);

MODULE_LICENSE("GPL");