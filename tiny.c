// http://stackoverflow.com/questions/5347805/how-to-compile-this-tiny-loadable-kernel-module-with-gcc
// http://askubuntu.com/questions/54239/problem-with-ioctl-in-a-simple-kernel-module
// http://linux.die.net/lkmpg/
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
#include <linux/fs.h>
#include <linux/device.h>
#include <asm/desc.h>

#include "tiny.h"

// http://www.linuxquestions.org/questions/linux-kernel-70/address-of-gdt-and-all-its-entries-933117/
static void dump_gdt(void) {
    struct desc_ptr gdtr;
    struct desc_struct *gdt;
    int i;

    native_store_gdt(&gdtr);
    printk("gdt.size    %d\n", gdtr.size);
    printk("gdt.address %08x\n", gdtr.address);
    gdt = (struct desc_struct*)gdtr.address;
    for (i = 0; i < gdtr.size; ++i) {
        if (gdt[i].a != 0 && gdt[i].b != 0)
            printk("gdt[%3d] %08x %08x\n", i, gdt[i].a, gdt[i].b);
    }
}

static int device_open(struct inode *inode, struct file *file)
{
    printk("device_open\n");
    return 0;
}

static long device_ioctl(struct file *filp,
                         unsigned int cmd, unsigned long args)
{
    switch(cmd)
    {
    case IOCTL_CMD:
        dump_gdt();
        break;
    }
    return 0;
}

static int device_release(struct inode *inode, struct file *file)
{
    printk("device_release\n");
    return 0;
}

static struct class *my_class;

static struct file_operations fops = {
    .open = device_open,
    .release = device_release,
    .unlocked_ioctl = device_ioctl
};

static int __init tiny_init(void)
{
    printk("tiny_init\n");
    major_no = register_chrdev(0, DEVICE_NAME, &fops);
    printk("DeviceName = %s Major_no = %d\n", DEVICE_NAME, major_no);
    my_class = class_create(THIS_MODULE, DEVICE_NAME);
    device_create(my_class, NULL, MKDEV(major_no,0), NULL, DEVICE_NAME);
    return 0;
}

static void __exit tiny_exit(void)
{
    printk("tiny_exit\n");
    device_destroy(my_class,MKDEV(major_no,0));
    class_unregister(my_class);
    class_destroy(my_class);
    unregister_chrdev(major_no, DEVICE_NAME);
}

module_init(tiny_init);
module_exit(tiny_exit);

MODULE_LICENSE("GPL");
