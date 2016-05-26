// http://stackoverflow.com/questions/5347805/how-to-compile-this-tiny-loadable-kernel-module-with-gcc
// Load:   insmod tiny.ko
// List:   lsmod
// Info:   modinfo tiny.ko
// Unload: rmmod tiny
// Log:    dmesg
//         tail /var/log/kern.log

#ifndef __KERNEL__
#define __KERNEL__
#endif
#ifndef MODULE
#define MODULE
#endif

#include <linux/module.h>
#include <linux/kernel.h>

static int __init tiny_init(void)
{
    printk(KERN_EMERG "Init.\n");
    return 0;
}

static void __exit tiny_exit(void)
{
    printk(KERN_EMERG "Exit.\n");
}

module_init(tiny_init);
module_exit(tiny_exit);
