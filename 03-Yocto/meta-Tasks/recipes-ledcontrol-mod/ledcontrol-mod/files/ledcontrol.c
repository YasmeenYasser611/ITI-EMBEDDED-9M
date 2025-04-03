#include <linux/proc_fs.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/io.h>
#include <linux/uaccess.h>

#define GPIO_BASE  0x3F200000  // Base address for GPIO (Raspberry Pi 3)
#define GPFSEL0    0x00        // GPIO Function Select 0
#define GPSET0     0x1C        // GPIO Pin Output Set 0
#define GPCLR0     0x28        // GPIO Pin Output Clear 0
#define GPIO_SIZE  0xB4        // Size to map all registers

#define LED_PIN    2  // GPIO2

static struct proc_dir_entry *proc_dir = NULL;
static void __iomem *gpio_base = NULL;

ssize_t mywrite(struct file *filp, const char __user *user, size_t size, loff_t *loff)
{
    char buff[10] = {0};  // Increased buffer size for safety
    void __iomem *gpset0, *gpclr0;

    if (size > sizeof(buff) - 1)
        size = sizeof(buff) - 1;

    if (copy_from_user(buff, user, size))
        return -EFAULT;

    if (!gpio_base)
        return -ENODEV;  // Ensure GPIO is mapped before accessing

    gpset0 = gpio_base + GPSET0;
    gpclr0 = gpio_base + GPCLR0;

    if (buff[0] == '1') {
        printk(KERN_INFO "GPIO %d Turned ON\n", LED_PIN);
        iowrite32((1 << LED_PIN), gpset0);
    } else if (buff[0] == '0') {
        printk(KERN_INFO "GPIO %d Turned OFF\n", LED_PIN);
        iowrite32((1 << LED_PIN), gpclr0);
    } else {
        return -EINVAL; // Invalid input
    }

    return size;
}

ssize_t myread(struct file *filp, char __user *user, size_t size, loff_t *loff)
{
    printk(KERN_INFO "LED Control: Read operation\n");
    return 0;
}

const struct proc_ops proc_file_operation = {
    .proc_read = myread,
    .proc_write = mywrite
};

static int __init proc_init(void)
{
    void __iomem *gpfsel0;
    uint32_t gpfsel_val;

    // Map the GPIO registers
    gpio_base = ioremap(GPIO_BASE, GPIO_SIZE);
    if (!gpio_base) {
        printk(KERN_ERR "Failed to map GPIO registers\n");
        return -ENOMEM;
    }

    gpfsel0 = gpio_base + GPFSEL0;

    // Configure GPIO2 as output
    gpfsel_val = ioread32(gpfsel0);
    gpfsel_val &= ~(0b111 << (LED_PIN * 3)); // Clear bits
    gpfsel_val |= (0b001 << (LED_PIN * 3));  // Set output mode
    iowrite32(gpfsel_val, gpfsel0);

    // Create proc file
    proc_dir = proc_create("led_Control", 0666, NULL, &proc_file_operation);
    if (!proc_dir) {
        iounmap(gpio_base);
        printk(KERN_ERR "Failed to create /proc/led_Control\n");
        return -ENOMEM;
    }

    printk(KERN_INFO "LED Control Driver Initialized\n");
    return 0;
}

static void __exit proc_exit(void)
{
    if (proc_dir)
        proc_remove(proc_dir);

    if (gpio_base)
        iounmap(gpio_base);

    printk(KERN_INFO "LED Control Driver Unloaded\n");
}

module_init(proc_init);
module_exit(proc_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Yasmeen");
MODULE_DESCRIPTION("Raspberry Pi LED Control Driver using /proc");
