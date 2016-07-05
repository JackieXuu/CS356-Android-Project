/*
 *Author: Zhengtian XU
 *StudentID: 5140309178
 *Problem: ptree system call
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/unistd.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <linux/prinfo.h>


MODULE_LICENSE("Dual BSD/GPL");
#define __NR_ptreecall 356

static int (*oldcall)(void);

/* Check whether the process has a child */ 
bool hasChildren(struct task_struct* task)
{
	if (task == NULL) return false;
	if (list_empty(&task->children)) return false;
	else return true;
}
/* Check whether the process has a brother */ 
bool hasSibling(struct task_struct* task)
{
	if (task == NULL) return false;
	struct list_head* head = &task->parent->children;
	if (list_is_last(&task->sibling, head)) return false;
	else return true;
}
/* Get a next process */
struct task_struct* getNext(struct task_struct* task)
{
	if (hasChildren(task)) return list_entry(task->children.next, struct task_struct, sibling);
	while (!hasSibling(task))
	{
		task = task->parent;
		if (task->pid == 0) return NULL;
	}
	return list_entry(task->sibling.next, struct task_struct, sibling);
}

/* Determine whether the task struct is a process. */
bool is_process(struct task_struct* task)
{
	if (task == NULL) return false;
	else
	{
		/* A process with no thread */
		if (thread_group_empty(task)) return true;	
		/* A process with at least 1 thread */
		if (thread_group_leader(task)) return true; 
	}
	return false;
}
/* Add the information of process into buf */
void addNode(struct task_struct* cur, struct prinfo* buf, int id)
{
	struct task_struct* children;
	struct task_struct* sibling;
	buf[id].state = cur->state;
	buf[id].pid = cur->pid;
	buf[id].parent_pid = cur->parent->pid;
	if (hasChildren(cur))
	{
		children = list_entry(cur->children.next, struct task_struct, sibling);
		buf[id].first_child_pid = children->pid;
	}
	else buf[id].first_child_pid = 0;
	if (hasSibling(cur))
	{
		sibling = list_entry(cur->sibling.next, struct task_struct, sibling);
		buf[id].next_sibling_pid = sibling->pid;
	}
	else buf[id].next_sibling_pid = 0;
	
	buf[id].uid = task_uid(cur);
	strncpy(buf[id].comm, cur->comm, 64);
}
/* DFS process */
int dfs(struct prinfo* buf, int *nr)
{
	int id = 0;
	/* initial process */
	struct task_struct* cur = &init_task;			
	int cnt = 0;
	while (cur != NULL)
	{
		if (!is_process(cur) || cur -> pid == 0)
		{
			cur = getNext(cur);
			continue;
		}	
		if (id < *nr) addNode(cur, buf, id++);
		cur = getNext(cur);
		cnt++;
	}
	*nr = id;
	return cnt;
}

static int sys_ptreecall(struct prinfo* buf, int *nr)
{
	int result = 0;
	if (*nr < 0 || buf == NULL || nr == NULL)
		return 0;
	read_lock(&tasklist_lock);
	result = dfs(buf, nr);
	read_unlock(&tasklist_lock);
	return result;
}

static int addsyscall_init(void)
{
	long *syscall = (long*)0xc000d8c4;
	oldcall = (int(*)(void))(syscall[__NR_ptreecall]);
	syscall[__NR_ptreecall] = (unsigned long) sys_ptreecall;
	printk(KERN_INFO "module load!\n");
	return 0;
}

static void addsyscall_exit(void)
{
	long *syscall = (long*) 0xc000d8c4;
	syscall[__NR_ptreecall] = (unsigned long) oldcall;
	printk(KERN_INFO "module exit!\n");
}

module_init(addsyscall_init);
module_exit(addsyscall_exit);