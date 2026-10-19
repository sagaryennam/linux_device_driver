#include<linux/module.h>
#include<linux/init.h>
#include<linux/fs.h>

int my_module_int(void);
void my_module_exit(void);

static int major ;

static char data_buf[64];
static char data_buf[64];

int my_open(struct inode *my_inode, struct file *fsp);
int my_release(struct inode *my_inode, struct file *fps);
ssize_t my_read(struct file *fsp, char __user *user_bufp, size_t len, loff_t *ofset);
ssize_t my_write(struct file *fsp, const char __user *user_bufp, size_t len, loff_t *ofset);
int my_module_init(void);
void my_module_exit(void);

struct file_operations fops = {
	.open = my_open ,
	.release = my_release,
	.read = my_read,
	.write = my_write,
};


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

ssize_t my_read(struct file *fsp, char __user *user_bufp, size_t len, loff_t *ofset)
{
	int not_copied, to_copy, delta;

	pr_info("Read Operation\n");

	to_copy = (len+*ofset)< sizeof(data_buf) ? len:  sizeof(data_buf) - *ofset ;
	pr_info("File Offset: %lldd,Copy byte size:%ld available bytes:%d",*ofset, len, to_copy);
       	
	if(*ofset > sizeof(data_buf))
	{
		return 0;
	}

	not_copied  = copy_to_user(user_bufp,&data_buf[*ofset], to_copy);
	delta = to_copy - not_copied;
	if(not_copied)
	{
		pr_warn("Left to read %d bytes", not_copied);
	}
	*ofset += delta ;
	return delta;	
}
ssize_t my_write(struct file *fsp, const char __user *user_bufp, size_t len, loff_t *ofset)
{
	int not_copied, to_copy, delta;

	pr_info("Write Operation\n");

	to_copy = (len+*ofset)< sizeof(data_buf) ? len:  sizeof(data_buf) - *ofset ;

	pr_info("File Offset: %lld,Copy byte size:%ld available bytes:%d",*ofset,len, to_copy ); 	

	if(*ofset > sizeof(data_buf))
	{
		return 0;
	}

	not_copied  = copy_from_user(&data_buf[*ofset], user_bufp, to_copy);
	delta = to_copy - not_copied;
	if(not_copied)
	{
		pr_warn("Left to write %d bytes", not_copied);
	}
	*ofset += delta ;
	return delta;	
	
}

int my_module_init(void)
{
	//If you pass '0' here this API automatically assigns major number,
	// else if you pass a number > 0,
	//then that will be assigned if number is available
	major = register_chrdev(0, "read_write_fs", &fops );
	if(major<0)
		pr_err("Error registering chrdev\n");
	pr_info("chrdev registered with Major Number:%d\n",major);
	return 0;
}

void my_module_exit(void)
{
	unregister_chrdev(major, "read_write_fs" );
	printk("Thsi is my_nodule_exit\n");
}

module_init(my_module_init);
module_exit(my_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sagar Yennam");
MODULE_DESCRIPTION("This module gives sample code for read & write operation");
