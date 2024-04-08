#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/i2c.h>
#include <linux/delay.h>
#include <linux/kernel.h>

#define I2C_BUS_AVAILABLE (1)
#define SLAVE_DEVICE_NAME ("CAP1188")
#define CAP1188_SLAVE_ADDR (0x29)

static struct i2c_adapter cap_i2c_adapter = NULL;
static struct i2c_client cap_i2c_client = NULL;

static int I2C_Write(unsigned char *buf, unsigned int len)
{
    int ret = i2c_master_send(cap_i2c_client, buf, len);
    return ret;
}

static int I2C_Read(unsigned char *out_buf, unsigned int len)
{
    int ret = i2c_master_recv(cap_i2c_client, out_buf, len)
    return ret;
}

//static void CAP1188_Write(bool is_cmd, unsigned char data)
//{
    //int ret;
    //ret = I2C_Write(buf, 2);
//}

/*static int CAP1188_Init(void)
{
    //write to registers 
    //CAP1188_Write(true, 0xaa)
}*/

static int cap_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
    //CAP1188_Init();
    pr_info("CAP1188 probed!!!\n");
}

static int cap_remove(struct i2c_client* client)
{
    pr_info("CAP1188 Removed!!!\n");
    return 0;
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
    }
    .probe = cap_probe,
    .remove = cap_remove,
    .id_table = cap_id,
};

static struct i2c_board_info cap_i2c_board_info = {
    I2C_BOARD_INFO(SLAVE_DEVICE_NAME, CAP1138_SLAVE_ADDR)
};

static int __init cap_driver_init(void)
{
    int ret = -1;
    cap_i2c_adapter = i2c_get_adapter(I2C_BUS_AVAILABLE);

    if()
}