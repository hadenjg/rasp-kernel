#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/i2c.h>
#include <linux/delay.h>
#include <linux/kernel.h>
#include <linux/sysfs.h>
#include <linux/kobject.h>

//--SYSFS DEFINITIONS------------------------------------------------------------------
static struct kobject *mymodule;
static int myvariable = 9;
static int sensor1 = 0;

static ssize_t myvariable_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    return sprintf(buf, "%d\n", myvariable);
}

static ssize_t sensor1_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    return sprintf(buf, "%d\n", sensor1);
}

//i'll leave this here as an example but my sensor info should be read only
/*static ssize_t myvariable_store(struct kobject *kobj, struct kobj_attribute *attr, char *buf, size_t count)
{
    sscanf(buf, "%du", &myvariable);
    return count;
}*/

//static struct kobj_attribute myvariable_attribute = __ATTR(myvariable, 0660, myvariable_show, (void *)myvariable_store);
static struct kobj_attribute myvariable_attribute = __ATTR_RO(myvariable);
static struct kobj_attribute sensor1_attribute = __ATTR_RO(sensor1);

//--CHAR DEV DEFINITIONS---------------------------------------------------------------

//#define DEVICE_NAME "cap1188" //dev name as it appears in /proc/devices
#define BUF_LEN 80 //max length of the message from the device

static int major; //major number assigned to the device driver

enum {
    CDEV_NOT_USED = 0,
    CDEV_EXCLUSIVE_OPEN = 1,
};

static atomic_t already_open = ATOMIC_INIT(CDEV_NOT_USED);

static char msg[BUF_LEN + 1];

static struct class *cls;

//--I2C DEV DEFINITIONS---------------------------------------------------------------

#define I2C_BUS_AVAILABLE (1)
#define SLAVE_DEVICE_NAME ("CAP1188")
#define CAP1188_SLAVE_ADDR (0x29)

static struct i2c_adapter *cap_i2c_adapter = NULL;
static struct i2c_client *cap_i2c_client = NULL;

//--I2C DEV FUNCTIONS-----------------------------------------------------------------

static int I2C_Write(char *buf, unsigned int len)
{
    int ret = i2c_master_send(cap_i2c_client, buf, len);
    return ret;
}

static int I2C_Read(char *out_buf, unsigned int len)
{
    int ret = i2c_master_recv(cap_i2c_client, out_buf, len);
    return ret;
}

static int cap_probe(struct i2c_client *client)//, const struct i2c_device_id *id)
{
    //CAP1188_Init();
    char buf[2] = {0};
    buf[0] = 0x74;
    buf[1] = 0xfe;
    I2C_Write(buf, 2);
    pr_info("CAP1188 probed!!!\n");


    char but[1] = {0};
    but[0] = 0x74;
    I2C_Write(but, 1);

    char testting = {0};
    I2C_Read(&testting, sizeof(testting));
    pr_info("CAP1188 this write does not destory the pi!!!\n");
    pr_info("I actually read back information!!!! it is this: %c. \n", testting);
    return 0;
}

static void cap_remove(struct i2c_client* client)
{
    char buf[2] = {0};
    buf[0] = 0x74;
    buf[1] = 0x00;
    I2C_Write(buf, 2);

    pr_info("CAP1188 Removed!!!\n");
}

static const struct i2c_device_id cap_id[] = {
    {SLAVE_DEVICE_NAME, 0},
    {}
};
MODULE_DEVICE_TABLE(i2c, cap_id);

static struct i2c_driver cap_driver = {
    .driver = {
        .name = SLAVE_DEVICE_NAME,
        .owner = THIS_MODULE,
    },
    .probe_new = cap_probe,
    .remove = cap_remove,
    .id_table = cap_id,
};

static struct i2c_board_info cap_i2c_board_info = {
    I2C_BOARD_INFO(SLAVE_DEVICE_NAME, CAP1188_SLAVE_ADDR)
};

//--CHAR DEVICE FUNCTIONS-----------------------------------------------------

static int cap1188_release(struct inode *inode, struct file *file)
{
	atomic_set(&already_open, CDEV_NOT_USED);
	module_put(THIS_MODULE);

    return 0;
}

static int cap1188_open(struct inode *inode, struct file *file)
{
    if(atomic_cmpxchg(&already_open, CDEV_NOT_USED, CDEV_EXCLUSIVE_OPEN)) 
        return -EBUSY;

    pr_info("I am attempting to open from the cap188 device driver?\n");
    try_module_get(THIS_MODULE);
    return 0;
}

static ssize_t cap1188_read(struct file *filp, char __user *buffer, size_t length, loff_t *offset)
{
    pr_info("I am reading from the cap1188 driver\n");
    //char but[] = {0x74};
    char but[] = {0x10};
    int len = sizeof(but); 
    ssize_t ret = len; 

    I2C_Write(but, len);

    char butter[2] = {0};
    I2C_Read(butter, sizeof(butter));
    sensor1 = (int)butter[0];

    /*if(*offset >= len || copy_to_user(buffer, butter, len))
    {
        pr_info("FAILED TO COPY TO user\n");
        ret = 0;
    }
    else
    {
        pr_info("COPY TO USER SUCCEEDED!!!!!\n");
        *offset += len;
    }*/

    return ret;
}

static ssize_t cap1188_write(struct file *filp, const char __user *buff, size_t len, loff_t *off)
{
    if(len > BUF_LEN)
        return -EINVAL;
    
    if(copy_from_user(msg, buff, len) != 0)
        return -EFAULT;

    pr_info("I am attempting to write to the cap1188 device driver!\n");

    I2C_Write(msg, len);
    return len;
}

struct file_operations cap1188_fops = {
	.owner = THIS_MODULE,
	.read = cap1188_read,
	.open = cap1188_open,
	.release = cap1188_release,
	.write = cap1188_write
};

//--DEVICE DRIVER BOILER PLATE CODE-------------------------------------------

static int __init cap_driver_init(void)
{
    int ret = -1;
    cap_i2c_adapter = i2c_get_adapter(I2C_BUS_AVAILABLE);

    if(cap_i2c_adapter != NULL)
    {
	    cap_i2c_client = i2c_new_client_device(cap_i2c_adapter, &cap_i2c_board_info);

	    if(cap_i2c_client != NULL)
	    {
		    i2c_add_driver(&cap_driver);
		    ret = 0;
	    }

	    i2c_put_adapter(cap_i2c_adapter);
    }

    //create char device
    major = register_chrdev(0, SLAVE_DEVICE_NAME, &cap1188_fops);

    if(major < 0) {
        pr_alert("Registering char device failed with %d\n", major);
	return major;
    }

    pr_info("I was assigned major number %d. \n", major);

    cls = class_create(THIS_MODULE, SLAVE_DEVICE_NAME);

    device_create(cls, NULL, MKDEV(major, 0), NULL, SLAVE_DEVICE_NAME);

    pr_info("Device created on /dev/%s\n", SLAVE_DEVICE_NAME);

// sysfs stuff -----------------------------------------------------------------------
    mymodule = kobject_create_and_add("cap1188", kernel_kobj);
    if(!mymodule)
        return -ENOMEM;

    ret = sysfs_create_file(mymodule, &myvariable_attribute.attr);

    if(ret) {
        pr_info("failed to create the myvariable file in /sys/kernel/cap1188");
    }

    ret = sysfs_create_file(mymodule, &sensor1_attribute.attr);

    if(ret) {
        pr_info("failed to create the sensor1 file in /sys/kernel/cap1188");
    }

// ----------------------------------------------------------------------------------
    pr_info("Driver Added!!!!\n");
    return ret;
}

static void __exit cap_driver_exit(void)
{
	i2c_unregister_device(cap_i2c_client);
	i2c_del_driver(&cap_driver);

	device_destroy(cls, MKDEV(major, 0));
	class_destroy(cls);
	unregister_chrdev(major, SLAVE_DEVICE_NAME);
    kobject_put(mymodule);
	pr_info("Driver Removed!!!\n");
}

module_init(cap_driver_init);
module_exit(cap_driver_exit);
//This should get rid of boiler plate code but I haven't been able to properly implement it
//module_i2c_driver(cap_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ME");
MODULE_DESCRIPTION("CAP1188 i2c driver");
MODULE_VERSION("1.0");
