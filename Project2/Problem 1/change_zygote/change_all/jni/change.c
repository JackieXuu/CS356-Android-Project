#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define DEFAULT_NUM 100
struct prinfo {
	pid_t parent_pid;		/* process id of parent */
	pid_t pid;			/* process id */
	pid_t first_child_pid;  	/* pid of youngest child */
	pid_t next_sibling_pid;  	/* pid of older sibling */
	long state;			/* current state of process */
	long uid;			/* user id of process owner */
	char comm[64];			/* name of program executed */
	int priority;
	int rt_priority;
	int sched_method;
};

void print(struct prinfo* buf, int nr)
{
	int id = 0;
	int matrix[nr];
	int cnt = 0;
	int i, j;
	matrix[0] = 0;
	for (i = 0; i < nr; ++i)
	{
		while (buf[i].parent_pid != matrix[cnt]) --cnt;
		for (j = 0; j < cnt; ++j) printf("\t");
		printf("%s,%d,%ld,%d,%d,%d,%ld,%d,%d,%d\n", buf[i].comm, buf[i].pid, buf[i].state,
					buf[i].parent_pid, buf[i].first_child_pid, buf[i].next_sibling_pid, buf[i].uid, 
					buf[i].sched_method, buf[i].priority, buf[i].rt_priority);
		++cnt;
		matrix[cnt] = buf[i].pid;
	}
}



int main(int argc, char** argv)
{
	struct prinfo* buf;
	int nr;
	int result = 0;
	int flag = 1;
	if (argc <= 1)
		nr = DEFAULT_NUM;
	else
	{
		int i = 0;
		for (; argv[1][i]!='\0'; ++i)
			if (!isdigit(argv[1][i])) flag = 0;
		if (!flag) nr = DEFAULT_NUM;
		else nr = atoi(argv[1]);
	}
	buf = calloc(nr, sizeof(struct prinfo));
	result = syscall(356, buf, &nr);
	print(buf, nr);
	printf("Total amount of processes: %d\n", result);


	int option;		//0->this process, 1->descendents of this process
	int name_pid;	//process name
	int policy;		//0->SCHED_NORMAL, 1->SCHED_FIFO, 2->SCHED_RR
	int priority;
	int pid;

	printf("Please input the changing model(0->this process, 1->descendents of this process):");
	scanf("%d", &option);
	while (option!=1 && option!=0)
	{
		printf("Input Error!\n");
		printf("Please input the changing model(0->this process, 1->descendents of this process):");
		scanf("%d", &option);
	}
	printf("Please input the pid of process:");
	scanf("%d", &name_pid);
	flag = 0;	//find the process
    int i = 0;
    while (i < nr) 
    {
        if (name_pid == buf[i].pid) 
        {
            pid = name_pid;
            flag = 1;
            break;
            printf("%d\n", i);
        }
        i++;
    }
    if (!flag) 
    {
        printf("Input Error! Because there is no such process!\n");
        exit(-1);
    }

    int descendents[200]={0};
    int des_num = 0;
    int j = 0;
    //change descendents
    if (option == 1)
    {
    	j = i++;
    	while (buf[i].parent_pid!=buf[j].parent_pid){
    		descendents[des_num] = buf[i].pid;
    		des_num++;
    		i++;
    	}
    }
    free(buf);

	printf("Please input the scheduler(0-SCHED_NORMAL, 1-SCHED_FIFO, 2-SCHED_RR):");
	scanf("%d",&policy);
	while (policy!=0 && policy!=1 && policy!=2)
	{
		printf("Please input the correct policy!\n");
		printf("Please input the scheduler(0-SCHED_NORMAL, 1-SCHED_FIFO, 2-SCHED_RR):");
		scanf("%d",&policy);
	}

	struct sched_param param;
	int maxprio,minprio;
	maxprio=sched_get_priority_max(policy);
	minprio=sched_get_priority_min(policy);
	printf("max priority:%d\n",maxprio);
	printf("min priority:%d\n",minprio);
	if (maxprio==-1) {
		perror("sched_get_priority_max error!\n");
		exit(1);
	}
	printf("Please input the priority:");
	scanf("%d",&priority);
    if (maxprio < 0 || maxprio > 99) {
        printf("Input Error! priority should between 0 with 99!\n");
        exit(-1);
    }
	param.sched_priority=priority;

	if (option == 0)
	{
		if (sched_setscheduler(pid,policy,&param)==-1) { 
			perror("sched_setscheduler() error!\n");
			exit(1);
		}
	}

	if (option == 1)
	{
		int i = 0;
		while (i < des_num)
		{
			if (sched_setscheduler(descendents[i],policy,&param)==-1) { 
				perror("sched_setscheduler() error!\n");
				exit(1);
			}
			++i;
		}
	}
	printf("\n");
	printf("\n");

	buf = calloc(nr, sizeof(struct prinfo));
	result = syscall(356, buf, &nr);
	print(buf, nr);
	printf("Total amount of processes: %d\n", result);
	free(buf);
}

