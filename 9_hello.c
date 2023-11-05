

#include <linux/kernel.h>
asmlinkage long sys_hello(void)
{
	printk(KERN_INFO "Hello world\n");
	return 0;
}
