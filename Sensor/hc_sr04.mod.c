#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif


static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0x5e9e3342, "gpio_to_desc" },
	{ 0x532543ff, "gpiod_get_raw_value" },
	{ 0xb43f9365, "ktime_get" },
	{ 0x637493f3, "__wake_up" },
	{ 0x92997ed8, "_printk" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0x32911460, "cdev_alloc" },
	{ 0x95c1026a, "cdev_add" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x47229b5c, "gpio_request" },
	{ 0xfe990052, "gpio_free" },
	{ 0x85f2e527, "gpiod_direction_output_raw" },
	{ 0x74cb8fc9, "gpiod_set_raw_value" },
	{ 0x15ac2962, "gpiod_direction_input" },
	{ 0xa0a28d3a, "gpiod_to_irq" },
	{ 0x92d5838e, "request_threaded_irq" },
	{ 0x5bbe49f4, "__init_waitqueue_head" },
	{ 0x3ea1b6e4, "__stack_chk_fail" },
	{ 0x8f678b07, "__stack_chk_guard" },
	{ 0x2bf9031b, "cdev_del" },
	{ 0xc1514a3b, "free_irq" },
	{ 0xca5a7528, "down_interruptible" },
	{ 0x8e865d3c, "arm_delay_ops" },
	{ 0x800473f, "__cond_resched" },
	{ 0xfe487975, "init_wait_entry" },
	{ 0x647af474, "prepare_to_wait_event" },
	{ 0x8ddd8aad, "schedule_timeout" },
	{ 0x49970de8, "finish_wait" },
	{ 0x51a910c0, "arm_copy_to_user" },
	{ 0x581cde4e, "up" },
	{ 0xc84d16dc, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "058950A94AA7DC9B96419D1");
