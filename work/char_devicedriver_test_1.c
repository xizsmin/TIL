#include <linux/init.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/sched.h>
#include <linux/device.h>
#include <linux/slab.h>
#include <asm/current.h>
#include <linux/uaccess.h>


#define DEVICE_NAME				"chardev"
#define DEVICE_FILE_NAME		"chardev"
#define MAJOR_NUM				100

static int chardev_open(struct inode *inode, struct file *file)
{
	printk("chardev_open\n");
	return 0;
}

struct file_operations chardev_fops = {
	.open = chardev_open,
};

static int chardev_init(void)
{
	int ret_val;
	ret_val = register_chrdev(MAJOR_NUM, DEVICE_NAME, &chardev_fops);

	if (ret_val < 0) {
		printk(KERN_ALERT "Sorry, registering chardev failed with %d\n", ret_val);
		return ret_val;
	}
  printk(KERN_INFO "Successfully registered device driver with major number %d\n", MAJOR_NUM);
  printk(KERN_INFO "TBD: mknod %s c %d 0\n", DEVICE_FILE_NAME, MAJOR_NUM);
  printk(KERN_INFO "echo \'A\' > chardev;dmesg\|tail");

	return 0;

}

static void chardev_exit(void)
{
	unregister_chrdev(MAJOR_NUM, DEVICE_NAME);
	printk("Successfully unregistered %s\n", DEVICE_NAME);
}

MODULE_LICENSE("GPL");
module_init(chardev_init);
module_exit(chardev_exit);
