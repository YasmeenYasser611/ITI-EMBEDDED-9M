#include <linux/module.h>
#include <linux/platform_device.h>
#include "device.h"

static void platform_device_release(struct device *dev)
{
    /* Managed resources are automatically freed */
}

static struct platform_device led_platform_devices[2] = {
    [0]={
        .name = "led1",
        .id = 0,
        .dev = {
            .release = platform_device_release,
        },
    },
    [1]={
        .name = "led2",
        .id = 1,
        .dev = {
            .release = platform_device_release,
        },
    }
};

static int __init led_devices_init(void)
{
    int ret;
    
    ret = platform_device_register(&led_platform_devices[0]);
    if (ret)
        return ret;
    
    ret = platform_device_register(&led_platform_devices[1]);
    if (ret) {
        platform_device_unregister(&led_platform_devices[0]);
        return ret;
    }
    
    return 0;
}

static void __exit led_devices_exit(void)
{
    platform_device_unregister(&led_platform_devices[0]);
    platform_device_unregister(&led_platform_devices[1]);
}

module_init(led_devices_init);
module_exit(led_devices_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Yasmeen");
MODULE_DESCRIPTION("LED Platform Devices");