#include <linux/init.h> //needed for macros
#include <linux/module.h> //needed for every module
#include <linux/printk.h> //needed for pr_info

MODULE_LICENSE("GPL");
MODULE_AUTHOR("LKMPG");
MODULE_DESCRIPTION("A sample driver");

static int hello3_data __initdata = 3;

static int __init hello_3_init(void)
{
  pr_info("Hello, world %d\n", hello3_data);
  return 0;
}

static void __exit hello_3_exit(void)
{
  pr_info("Goodbye, world 3\n");
}

module_init(hello_3_init);
module_exit(hello_3_exit);


