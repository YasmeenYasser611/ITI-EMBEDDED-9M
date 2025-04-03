#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>

/*function prototypes*/
ssize_t	read(struct file *, char __user *, size_t, loff_t *);
ssize_t	write (struct file *, const char __user *, size_t, loff_t *);
int	open (struct inode *, struct file *);
int	release (struct inode *, struct file *);

static dev_t _dev;
static struct cdev _cdev = {
    .owner = THIS_MODULE
};
static const struct file_operations _fops = {
    // .read = read,
    .write = write,
};



ssize_t	write (struct file *flip, const char __user *user, size_t size, loff_t *offst)
{
    printk("write on systemcall \n");
    return size;
}


static __init int my_driver_init(void)
{
    int status = 0;
    /*allocate device regions*/
    alloc_chrdev_region(&_dev, 0, 1, "mydevice");
    /*assign file operation to the cdev struct that owned by the character device*/
    cdev_init(&_cdev, &_fops);
    status = cdev_add(&_cdev, _dev, 1);

    printk("my major: %d, my minor: %d \n", MAJOR(_dev), MINOR(_dev));
    return status;
}

static __exit void my_driver_exit(void)
{
    /* delete the object for the devices*/
    cdev_del(&_cdev);
    /* deallocate the region */
    unregister_chrdev_region(_dev, 1);
}

module_init(my_driver_init);
module_exit(my_driver_exit);

MODULE_LICENSE("GPL");
