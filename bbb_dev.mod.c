#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xae4b0ceb, "module_layout" },
	{ 0x35b6b772, "param_ops_charp" },
	{ 0x40a6f522, "__arm_ioremap" },
	{ 0xb0fab0ca, "__mutex_init" },
	{ 0x6c4fc9f7, "device_create" },
	{ 0x95d52825, "__class_create" },
	{ 0xcd7317e5, "__register_chrdev" },
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0x2f729c13, "class_destroy" },
	{ 0xab0768a8, "class_unregister" },
	{ 0xb45e1167, "device_destroy" },
	{ 0xf41404d5, "mutex_destroy" },
	{ 0x9d669763, "memcpy" },
	{ 0x97255bdf, "strlen" },
	{ 0x95d01c5a, "vfs_write" },
	{ 0xc6a551a4, "filp_close" },
	{ 0xa60379af, "filp_open" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
	{ 0xcd136724, "mutex_trylock" },
	{ 0x2e5810c6, "__aeabi_unwind_cpp_pr1" },
	{ 0x27e1a049, "printk" },
	{ 0x48efa767, "mutex_unlock" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "5B3BDF7E754DD6CD520E567");
