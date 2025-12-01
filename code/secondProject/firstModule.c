#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Gunn");
MODULE_DESCRIPTION("A simple example of a Linux kernel module.");

static int __init helloInit(void) {
    printk(KERN_INFO "Hello, module loaded.\n");

    return 0;
}

static void __exit helloExit(void) {
    printk(KERN_INFO "Hello, module unloaded.\n");
}

module_init(helloInit);
module_exit(helloExit);