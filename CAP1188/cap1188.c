#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/i2c.h>
#include <linux/delay.h>
#include <linux/kernel.h>

#define I2C_BUS_AVAILABLE (1)
#define SLAVE_DEVICE_NAME ("CAP1188")
#define CAP1188_SLAVE_ADDR (0x29)

static struct i2c_adapter *cap_i2c_adapter = NULL;
static struct i2c_client *cap_i2c_client = NULL;

static int I2C_Write(unsigned char *buf, unsigned int len)
{
    int ret = i2c_master_send(cap_i2c_client, buf, len);
    return ret;
}

static int I2C_Read(unsigned char *out_buf, unsigned int len)
{
    int ret = i2c_master_recv(cap_i2c_client, out_buf, len);
    return ret;
}

//static void CAP1188_Write(bool is_cmd, unsigned char data)
//{
    //int ret;
    //ret = I2C_Write(buf, 2);
//}

//static int CAP1188_Init(void)
//{
    //write to registers 
    //CAP1188_Write(true, 0x74)
//}

static int cap_probe(struct i2c_client *client)//, const struct i2c_device_id *id)
{
    //CAP1188_Init();
    unsigned char buf[2] = {0};
    buf[0] = 0x74;
    buf[1] = 0xfe;
    I2C_Write(buf, 2);
    pr_info("CAP1188 probed!!!\n");
    return 0;
}

static void cap_remove(struct i2c_client* client)
{
    unsigned char buf[2] = {0};
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

//static const struct of_device_id cap_of_match[] = {
	//{.compatible = "

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
    pr_info("Driver Added!!!!\n");
    return ret;
}

static void __exit cap_driver_exit(void)
{
	i2c_unregister_device(cap_i2c_client);
	i2c_del_driver(&cap_driver);
	pr_info("Driver Removed!!!\n");
}

module_init(cap_driver_init);
module_exit(cap_driver_exit);
//module_i2c_driver(cap_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ME");
MODULE_DESCRIPTION("CAP1188 i2c driver");
MODULE_VERSION("1.0");
