#include<linux/module.h>
#include<linux/init.h>
int my_module_int(void);
void my_module_exit(void);
int my_module_init(void)
{
	printk("This is my_module_init\n");
	return 0;
}

void my_module_exit(void)
{
	printk("Thsi is my_nodule_exit\n");
}

module_init(my_module_init);
module_exit(my_module_exit);

MODULE_LICENSE("GPL");
