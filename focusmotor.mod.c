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
};

static const struct modversion_info ____versions[]
__attribute_used__
__attribute__((section("__versions"))) = {
	{ 0x79021143, "struct_module" },
	{ 0xaa136450, "param_get_charp" },
	{ 0x2cd7da6c, "param_set_charp" },
	{ 0x89b301d4, "param_get_int" },
	{ 0x98bd6f46, "param_set_int" },
	{ 0x91fbf659, "wait_for_completion_interruptible" },
	{ 0x4ba89b2e, "malloc_sizes" },
	{ 0xfcec0987, "enable_irq" },
	{ 0x3ce4ca6f, "disable_irq" },
	{ 0xb794c614, "request_irq" },
	{ 0x84b183ae, "strncmp" },
	{ 0x2d4f6c22, "init_timer" },
	{ 0xfa2a45e, "__memzero" },
	{ 0xe521e876, "kmem_cache_alloc" },
	{ 0xa8f59416, "gpio_direction_output" },
	{ 0xc4922191, "complete" },
	{ 0x74cc238d, "current_kernel_time" },
	{ 0xd05d837c, "register_chrdev" },
	{ 0x381f6ad5, "init_waitqueue_head" },
	{ 0xc40f91c2, "gpio_set_value" },
	{ 0x37a0cba, "kfree" },
	{ 0xf20dabd8, "free_irq" },
	{ 0x801678, "flush_scheduled_work" },
	{ 0xdd132261, "printk" },
	{ 0xc192d491, "unregister_chrdev" },
	{ 0x1042cbb5, "__up_wakeup" },
	{ 0x829871bc, "__down_interruptible_failed" },
};

static const char __module_depends[]
__attribute_used__
__attribute__((section(".modinfo"))) =
"depends=";

