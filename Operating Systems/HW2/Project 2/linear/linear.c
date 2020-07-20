// Phong Nguyenho - ph094398
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>

int linear_init(void)
{
	printk(KERN_INFO "Loading Module\n");

	struct task_struct *task;

	for_each_process(task)
	{
		printk(KERN_INFO "Process Name: %s State: %ld PID: %d\n", task->comm, task->state, task->pid);
	}

	return 0;
}

void linear_exit(void)
{
	printk(KERN_INFO "Removing Module.\n");
}

module_init(linear_init);
module_exit(linear_exit);