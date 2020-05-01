// simple example for creating and registering a character device driver
// defining basic fops for reading/writing to the device

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


#define DRIVER_NAME				"chardev"
#define BUFFER_SIZE				256

static const unsigned int MINOR_BASE = 0;
static const unsigned int MINOR_NUM = 2;
static unsigned int chardev_major;
static struct cdev chardev_cdev;
static struct class *chardev_class = NULL;

static int chardev_open(struct inode *, struct file *);
static int chardev_release(struct inode *, struct file *);
static ssize_t chardev_read(struct file *, char *, size_t, loff_t *);
static ssize_t chardev_write(struct file *, const char *, size_t, loff_t *);

struct file_operations chardev_fops = {
	.open = chardev_open,
	.release = chardev_release,
	.read = chardev_read,
	.write = chardev_write,
};

struct data {
	unsigned char buffer[BUFFER_SIZE];
};

static int chardev_init(void)
{
	int alloc_ret = 0;
	int cdev_err = 0;
	int minor;
	dev_t dev;
	
	printk("chardev_init() called\n");

	// 1. register char device number to system
	alloc_ret = alloc_chrdev_region(&dev, MINOR_BASE, MINOR_NUM, DRIVER_NAME);
	if (alloc_ret) {
		printk(KERN_ERR "alloc_chrdev_region = %d\n", alloc_ret);
		return -1;
	}

	// 2. retrieve major/minor number for device driver
	chardev_major = MAJOR(dev);
	dev = MKDEV(chardev_major, MINOR_BASE);

	printk(KERN_INFO "major=%u, minor=%d, dev_t=%u\n", chardev_major, MINOR_BASE, dev);

	// 3. initialize chardev_cdev
	cdev_init(&chardev_cdev, &chardev_fops);
	chardev_cdev.owner = THIS_MODULE;

	// 4. add a char device to system
	cdev_err = cdev_add(&chardev_cdev, dev, MINOR_NUM);
	if (cdev_err) {
		printk(KERN_ERR "cdev_add = %d\n", cdev_err);
		unregister_chrdev_region(dev, MINOR_NUM);
		return -1;
	}
	// 5. create class for device to create
	chardev_class = class_create(THIS_MODULE, "chardev");
	if (IS_ERR(chardev_class)) {
		printk(KERN_ERR "class_create\n");
		cdev_del(&chardev_cdev);
		unregister_chrdev_region(dev, MINOR_NUM);
		return -1;
	}
	// 6. create device
	for(minor = MINOR_BASE; minor < MINOR_BASE + MINOR_NUM; ++minor) {
		printk(KERN_INFO "[creating chardev] chardev%d\n", minor);
		device_create(chardev_class, NULL, MKDEV(chardev_major, minor), NULL, "chardev%d", minor);
	}

	return 0;
}

static void chardev_exit(void)
{
	int minor;
	dev_t dev = MKDEV(chardev_major, MINOR_BASE);
	printk("chardev_exit() called\n");

	// 1. destroy devices created by device_create()
	for(minor = MINOR_BASE; minor < MINOR_BASE + MINOR_NUM; ++minor) \
		device_destroy(chardev_class, MKDEV(chardev_major, minor));

	// 2. destroy class created by class_create()
	class_destroy(chardev_class);

	// 3. remove chardev added by cdev_add()
	cdev_del(&chardev_cdev);

	// 4. unregister device number registered by alloc_chrdev_region()
	unregister_chrdev_region(dev, MINOR_NUM);

	printk("Successfully unregistered %s\n", DRIVER_NAME);
}

static int chardev_open(struct inode *inode, struct file *file)
{
	printk("chardev_open() called\n");
	char *str = "Helloworld";
	int ret;

	struct data *p = kmalloc(sizeof(struct data), GFP_KERNEL);
	if (!p) {
		printk(KERN_ERR "kmalloc - Null\n");
		return -ENOMEM;
	}
	ret = strlcpy(p->buffer, str, sizeof(p->buffer));
	if (ret > strlen(str)) printk(KERN_ERR "strlcpy - too long (%d)\n", ret);

	file->private_data = p;

	return 0;
}

static int chardev_release(struct inode *inode, struct file *file)
{
	printk("chardev_release() called\n");
	if (file->private_data) {
		kfree(file->private_data);
		file->private_data = NULL;
	}
	return 0;
}

// called when data transferred from user space to the device
static ssize_t chardev_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos)
{
	struct data *p = filp->private_data;
	printk("chardev_write() called\n");
	printk("Before calling copy_from_user() function: %p, %s\n", p->buffer, p->buffer);

	// copy buf(data from user space) to p->buffer
	if (copy_from_user(p->buffer, buf, count) != 0) return -EFAULT;

	printk("After calling copy_from_user() function: %p, %s\n", p->buffer, p->buffer);
	return count;
}

// called when data transferred from device to user space
static ssize_t chardev_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
	printk("chardev_read() called\n");
	struct data *p = filp->private_data;

	if (count > BUFFER_SIZE) count = BUFFER_SIZE;
	if (copy_to_user(buf, p->buffer, count) != 0) return -EFAULT;
	return count;
}

MODULE_LICENSE("Dual BSD/GPL");
module_init(chardev_init);
module_exit(chardev_exit);
