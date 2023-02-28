//write a simple "Hello, world!" kernel module, extend your kernel module to print the following information to the kernel log:
//1 The name and PID of the current process .
//2 The name and PID of the parent process .
//Extend your kernel module to walk the process tree, starting from the current process, until you reach the process with pid 0

#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>//

#include <linux/kernel.h> //The linux/kernel.h header which gets used for module builds is the header which is part of the kernel source. When				 modules are built in the kernel source tree, that’s the version which is used.

//MODULE_LICENSE("GPL");
//MODULE_AUTHOR("hellow");
//MODULE_DESCRIPTION("A simple 'Hello, world!' kernel module");


static int __init hello_init(void)
{
	// task_struct structure contains all the information about a process. 	
    struct task_struct *task, *parent_task;
    task = current;
    parent_task = task->parent;

    printk(KERN_INFO "Hello, world!\n");
    printk(KERN_INFO "Current process: name=%s, pid=%d\n", task->comm, task->pid);
    printk(KERN_INFO "Parent process: name=%s, pid=%d\n", parent_task->comm, parent_task->pid);

    while (task->pid != 0)
    {
        task = task->parent;
        printk(KERN_INFO "Process in tree: name=%s, pid=%d\n", task->comm, task->pid);
    }

    return 0;
}

static void __exit hello_exit(void)
{
    printk(KERN_INFO "Goodbye, world!\n");
}

module_init(hello_init);
module_exit(hello_exit);

