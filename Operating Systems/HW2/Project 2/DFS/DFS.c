// Phong Nguyenho - ph094398
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>

void dfs(struct task_struct *task)
{
	struct task_struct *task_next;
	struct list_head *list;

	list_for_each(list, &task->children) 
	{
		task_next = list_entry(list, struct task_struct, sibling);

		printk(KERN_INFO "Process Name: %s State: %ld PID: %d\n", task_next->comm, task_next->state, task_next->pid);

		dfs(task_next);
	}  
}

int dfs_init(void)
{
	printk(KERN_INFO "Loading Module\n");

	dfs(&init_task);
	
	return 0;
}

void dfs_exit(void)
{
	printk(KERN_INFO "Removing Module\n");
}

module_init(dfs_init);
module_exit(dfs_exit);