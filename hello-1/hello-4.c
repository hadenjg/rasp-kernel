#include <linux/init.h>
#include <linux/kernel.h>  //for ARRAY_SIZE()
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/printk.h>
#include <linux/stat.h>

MODULE_LICENSE("GPL");

static short int myshort = 1;
static int myint = 420;
static long int mylong =9999;
static char *mystring = "blah";
static int myintarray[2] = { 420, 420 };
static int arr_argc = 0;

/* module_param(foo, int, 0000)
 * the first param is the parameters name
 * the second param is its data type
 * the final argument is the permissions bits,
 * for exposing parameters in sysfs (if non-zero) at a later stage.
 */
module_param(myshort, short, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(myshort, "A short integer");
module_param(myint, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(myint, "An integer");
module_param(mylong, long, S_IRUSR);
MODULE_PARM_DESC(mylong, "A long integer");
module_param(mystring, charp, 0000);
MODULE_PARM_DESC(mystring, "A character string");

/* module_param_array(name, type, num, perm)
 * The first param is the parameter's (in this case the array's) name
 * the second param is the data type of the elements of the array
 * the third argument is a pointer to the variable that will store the number
 * of elements of the array initialized by the user at module loading time
 * the fourth argument is the permission bits
 */
module_param_array(myintarray, int, &arr_argc, 0000);
MODULE_PARM_DESC(myintarray, "An array of integers");

static int __init hello_4_init(void)
{
  int i;

  pr_info("Hello, world 4\n==============\n");
  pr_info("myshort is a short integer: %hd\n", myshort);
  pr_info("myint is an integer: %d\n", myint);
  pr_info("mylong is a long integer: %ld\n", mylong);
  pr_info("mystring is a string: %s\n", mystring);

  for(i =0; i< ARRAY_SIZE(myintarray); i++)
  {
    pr_info("myintarray[%d] = %d\n", i, myintarray[i]);
  }
  
  pr_info("got %d arguments for myintarray.\n", arr_argc);
  return 0;
}

static void __exit hello_4_exit(void)
{
  pr_info("Goodbye, world 4 \n");
}

module_init(hello_4_init);
module_exit(hello_4_exit);
