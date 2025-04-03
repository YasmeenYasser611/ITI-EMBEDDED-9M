#include <linux/module.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>  // Required for copy_to_user & copy_from_user

#define SIZE_ARRAY 10

/* Function prototypes */
ssize_t my_proc_read(struct file *, char __user *, size_t, loff_t *);
ssize_t my_proc_write(struct file *, const char __user *, size_t, loff_t *);
int my_proc_open(struct inode *, struct file *);
int my_proc_release(struct inode *, struct file *);

static struct proc_dir_entry *proc_dir;
static char buffArr[SIZE_ARRAY] = {0};
static int count = 0;

static struct proc_ops fops = {
    .proc_read = my_proc_read,
    .proc_write = my_proc_write,
    .proc_open = my_proc_open,
    .proc_release = my_proc_release,
};

/* Read Function */
ssize_t my_proc_read(struct file *flip, char __user *user, size_t size, loff_t *offst)
{
    if (*offst >= count)
        return 0;  // EOF (Nothing left to read)

    if (size > count - *offst)
        size = count - *offst;  // Read only available data

    if (copy_to_user(user, buffArr + *offst, size))
        return -EFAULT;

    *offst += size;  // Move offset forward

    // shift buffer and update count
    if (*offst > 0) 
    {  
        int remaining = count - *offst;
        
        if (remaining > 0) 
        {
            memmove(buffArr, buffArr + *offst, remaining);
        }
        
        count = remaining;  // Update count after shifting
        *offst = 0;  // Reset offset
    }

    return size;
}




/* Write Function */
ssize_t my_proc_write(struct file *flip, const char __user *user, size_t size, loff_t *offst)
{
    if (count >= SIZE_ARRAY)
        return -ENOMEM;  // Buffer full

    if (size > SIZE_ARRAY - count)
        size = SIZE_ARRAY - count;  // Store only remaining space

    if (copy_from_user(buffArr + count, user, size))
        return -EFAULT;

    count += size;
    
    return size;
}

int my_proc_open(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "Proc file opened\n");
    return 0;
}

int my_proc_release(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "Proc file closed\n");
    return 0;
}

static __init int myproc_init(void)
{
    proc_dir = proc_create("mydriver", 0666, NULL, &fops);
    if(NULL == proc_dir)
    {
        printk(KERN_ERR "Error creating proc file\n");
        return -EIO;
    }
    printk(KERN_INFO "Proc file created\n");
    return 0;
}

static __exit void myproc_exit(void)
{
    proc_remove(proc_dir);
    printk(KERN_INFO "Proc file removed\n");
}

module_init(myproc_init);
module_exit(myproc_exit);

MODULE_LICENSE("GPL");



// fady:

// ssize_t	my_proc_read(struct file *flip, char __user *user, size_t size, loff_t *offst){
//     printk("Open file \n");

//     if(size < SIZE_ARRAY && count > size)
//     {
//         copy_to_user(user, buffArr, size);
//         count = count - size;
//     }
//     else if(size > SIZE_ARRAY && count == 10)
//     {
//         size = SIZE_ARRAY;
//         copy_to_user(user, buffArr, size);
//         count = 0;
//     }
//     else
//     {
//         return -E2BIG;
//     }
//     return size;

// }

// ssize_t	my_proc_write (struct file *flip, const char __user *user, size_t size, loff_t *offst)
// {
//     printk("write on buffer \n");
//     char localVar = 0;

//     if(size > SIZE_ARRAY)
//     {
//         size = SIZE_ARRAY;
//     }
//     if(count < 10)
//     {
//         localVar = size + count;
//         copy_from_user(buffArr, user, localVar);
//         count = count + localVar;
//     }
//     else 
//     {
//         printk("error in write\n");
//         return ENOMEM;
//     }

//     return localVar;
// }


