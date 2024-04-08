#include <linux/cdev.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>
#include <linux/kdev_t.h>
#include <linux/module.h>
#include <linux/semaphore.h>
#include <linux/timekeeping.h>
#include <linux/uaccess.h>
#include <linux/wait.h>
#include <asm/atomic.h>

#define GPIO_RST  (6)

struct cdev *cap1188_cdev;
int drv_major = 0;
int gpio_irq_number;

wait_queue_head_t wait_for_echo;
volatile int condition_echo;

// Only one process shall be able to open the device at the same time
atomic_t opened = ATOMIC_INIT(-1);

// Only one thread of execution shall read at the same time since a read triggers a HW measurement
DEFINE_SEMAPHORE(read_semaphore);

ssize_t cap1188_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
    /*if (*f_pos > 0) {
        return 0; // EOF
    }

    if (copy_to_user(buf, &range_mm, sizeof(range_mm))) {
        return -EFAULT;
    }

    *f_pos += sizeof(range_mm);

    return sizeof(range_mm);*/
    return 0;
}

int cap1188_open(struct inode *inode, struct file *filp) {
    // Allow only one process to open the device at the same time
    /*if (atomic_inc_and_test(&opened)) {
        return 0;
    }
    else {
        return -EBUSY;
    }*/
    return 0;
}

int cap1188_release(struct inode *inode, struct file *filp) {
    //atomic_set(&opened, -1);
	return 0;
}

struct file_operations cap1188_fops = {
	.owner =     THIS_MODULE,
	.read =	     cap1188_read,
	.open =	     cap1188_open,
	.release =   cap1188_release
};

static int cap1188_init(void)
{
    int result;
    dev_t dev = MKDEV(drv_major, 0);

    pr_info("[CAP1188]: Initializing CAP1188\n");

    result = alloc_chrdev_region(&dev, 0, 1, "cap1188");
    drv_major = MAJOR(dev);

    if (result < 0) {
        pr_alert("[CAP1188]: Error in alloc_chrdev_region\n");
        return result;
    }

    cap1188_cdev = cdev_alloc();
    cap1188_cdev->ops = &cap1188_fops;

    result = cdev_add(cap1188_cdev, dev, 1);
    if (result < 0) {
        pr_alert("[CAP1188]: Error in cdev_add\n");
        unregister_chrdev_region(dev, 1);
        return result;
    }

    return 0;
}

static void cap1188_exit(void)
{
    dev_t dev = MKDEV(drv_major, 0);
    cdev_del(cap1188_cdev);

    unregister_chrdev_region(dev, 1);

    pr_info("[CAP1188]: Exit CAP1188\n");
}


MODULE_AUTHOR("ME");
MODULE_DESCRIPTION("Linux device driver for CAP1188 ultrasonic distance sensor");
MODULE_LICENSE("GPL");

module_init(cap1188_init);
module_exit(cap1188_exit);