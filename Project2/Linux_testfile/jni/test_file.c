/*
 *Author: Zhengtian XU
 *StudentID: 5140309178
 *Problem: linux test file
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sched.h>

#define COUNT 300000000
unsigned long long result = 0;;

void test_func()
{
	int i = 0;

    for(i = 0; i<600000;i++)
    {
        result += 2;
    }
}

int main(int argc, char const *argv[])
{
	clock_t start, end;
	int i, maxprio, policy;
	struct sched_param param;
	if (argc == 2)
	{
		policy = atoi(argv[1]);
		if (policy == 0 || policy == 1 || policy == 2)
			maxprio=sched_get_priority_max(policy);
		else {perror("You must enter a scheduling policy number!\n");exit(1);}
	}
	else if (argc == 3)
	{
		policy = atoi(argv[1]);
		if (!(policy == 0 || policy == 1 || policy || 2))
			{perror("You must enter a scheduling policy number!\n");exit(1);}
		maxprio = atoi(argv[2]);
		if (maxprio < sched_get_priority_min(policy) || maxprio > sched_get_priority_max(policy))
			{perror("You must enter a corrext priority number!\n");exit(1);}
	}
	else {perror("You must enter 2 or 3 parameters!\n");exit(1);}

	param.sched_priority=maxprio;
	if (sched_setscheduler(getpid(),policy,&param)==-1) { 
		perror("sched_setscheduler() error!\n");
		exit(1);
	}
	start = clock();
	for (i = 0; i < COUNT; ++i) test_func();
	end = clock();
	double duration = (double)(end - start) / CLOCKS_PER_SEC;
	printf("%f seconds!\n", duration);
	return 0;
}