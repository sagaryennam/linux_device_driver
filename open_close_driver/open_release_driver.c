#include<linux/module.h>
#include<linux/init.h>
#include<linux/fs.h>

int my_module_int(void);
void my_module_exit(void);

static int major ;

int my_open(struct inode *my_inode, struct file *fsp)
{
	pr_info("Major_number=%d Minor_number=%d\n",imajor(my_inode),iminor(my_inode));
	return 0;
}

int my_release(struct inode *my_inode, struct file *fps)
{
	pr_info("File relased\n");
	return 0;
}

struct file_operations fops = {
	.open = my_open ,
	.release = my_release,
};

int my_module_init(void)
{
	//If you pass '0' here this API automatically assigns major number,
	// else if you pass a number > 0,
	//then that will be assigned if number is available
	major = register_chrdev(0, "open_close_fs", &fops );
	if(major<0)
		pr_err("Error registering chrdev\n");
	pr_info("chrdev registered with Major Number:%d\n",major);
	return 0;
}

void my_module_exit(void)
{
	printk("Thsi is my_nodule_exit\n");
}

module_init(my_module_init);
module_exit(my_module_exit);

MODULE_LICENSE("GPL");
