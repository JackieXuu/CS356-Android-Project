/*
 *Author: Zhengtian XU
 *StudentID: 5140309178
 *Problem: Scheduler Changing
 */

#include <stdio.h>
#include <sched.h>
#include <stdlib.h>

int main()
{
	int pid, policy = 0, prio;
	printf("Please input pid:");
	scanf("%d",&pid);
	int sched=sched_getscheduler(pid);
	printf("formal policy:%d\n",sched);
	printf("Please input the scheduler(0-SCHED_NORMAL, 1-SCHED_FIFO, 2-SCHED_RR):");
	scanf("%d",&policy);
	while (policy!=0 && policy!=1 && policy!=2)
	{
		printf("Please input the correct policy!\n");
		printf("Please input the scheduler(0-SCHED_NORMAL, 1-SCHED_FIFO, 2-SCHED_RR):");
		scanf("%d",&policy);
	}
	struct sched_param param;
	int maxprio;
	maxprio=sched_get_priority_max(policy);
	printf("max priority:%d\n",maxprio);
	if (maxprio==-1) {
		perror("sched_get_priority_max error!\n");
		exit(1);
	}
	printf("Please input the priority:");
	scanf("%d",&prio);
	param.sched_priority=prio;
	if (sched_setscheduler(pid,policy,&param)==-1) { 
		perror("sched_setscheduler() error!\n");
		exit(1);
	}
	sched=sched_getscheduler(pid);
	printf("now Policy:%d\n",sched);
	printf("now max priority:%d\n",sched_get_priority_max(sched));
	printf("now min priority:%d\n",sched_get_priority_min(sched));
	return 0;
}