#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kd.h>
#include <linux/kobject.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/string.h>
#include <linux/sysfs.h>
#include <linux/vt_kern.h>

static int ledctl;
struct tty_driver *my_driver;

static ssize_t store(struct kobject *kobj, struct kobj_attribute *attr,
					 const char *buf, size_t count) {
	sscanf(buf, "%du", &ledctl);
	ledctl &= 7;
	(my_driver->ops->ioctl)(vc_cons[fg_console].d->port.tty, KDSETLED, ledctl);
	return count;
}

static struct kobj_attribute ledattr = __ATTR(ledctl, 0220, 0, store);

static int __init sys_init(void) {
	int error = 0;

	pr_debug("Module initialized successfully\n");

	my_driver = vc_cons[fg_console].d->port.tty->driver;

	error = sysfs_create_file(kernel_kobj, &ledattr.attr);
	if (error) {
		pr_debug("failed to create the file /sys/kernel/ledctl\n");
	}

	return error;
}

static void __exit sys_exit(void) {
	pr_debug("Module unloaded successfully\n");
	sysfs_remove_file(kernel_kobj, &ledattr.attr);
	(my_driver->ops->ioctl)(vc_cons[fg_console].d->port.tty, KDSETLED, 0xff);
}

MODULE_LICENSE("GPL");
module_init(sys_init);
module_exit(sys_exit);