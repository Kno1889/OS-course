#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gcd.h>
#include <asm/param.h>
#include <linux/sched.h>

void print_init_PCB(void)
{
       // Process Control Block, represented by task_struct data type. Relevant attributes
       printk(KERN_INFO "init_task pid: %d", init_task.pid); // Process ID
       printk(KERN_INFO "init_task state: %d", init_task.__state); // Process state
       printk(KERN_INFO "init_task flags: %d", init_task.flags); // flags
       printk(KERN_INFO "init_task runtime priority: %d", init_task.rt_priority); // runtime priority
       printk(KERN_INFO "init_task process policy: %d", init_task.policy); // process policy
       printk(KERN_INFO "init_task task group id: %d", init_task.tgid); // task group id
}

/* This function is called when the module is loaded. */
int simple_init(void)
{
       printk(KERN_INFO "Loading Module\n");
       print_init_PCB();

	printk(KERN_INFO "HZ = %d\n",HZ);
	printk(KERN_INFO "jiffies = %lu\n",jiffies);

       return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void) {
	printk(KERN_INFO "Removing Module\n");

        printk(KERN_INFO "%lu\n", gcd(3300,24));
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");

