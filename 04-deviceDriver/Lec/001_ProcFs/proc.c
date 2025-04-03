#include <linux/proc_fs.h>
#include <linux/init.h>
#include <linux/module.h>

struct proc_dir_entry * proc_dir = NULL;

ssize_t	mywrite (struct file *filp, const char __user *user, size_t size, loff_t *loff)
{
    char buff[2] = {0};
    copy_from_user(buff, user, size);
    
    printk("hello from write %c \n", buff[0]);
    if(buff[0] == 1)
    {
        gpio_on();
    }
    else
    {
        gpio_off();
    }

    return size;
}
ssize_t	myread (struct file *filp, char __user *user, size_t size, loff_t *loff)
{
    printk("hello from read \n");
    return 0;
}


const struct proc_ops proc_file_operation = {
    .proc_read = myread,
    .proc_write = mywrite
};

static __init int proc_init(void)
{
    /*create proc file under proc fs*/
    proc_dir = proc_create("hotmail", 0666, NULL, &proc_file_operation);
    printk("hello from init \n");
    return 0;
}

static __exit void proc_exit(void)
{
    proc_remove(proc_dir);
    printk("hello from exit \n");
}

module_init(proc_init);
module_exit(proc_exit);

MODULE_LICENSE("GPL");





