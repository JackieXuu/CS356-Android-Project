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

int main()
{
	clock_t start, end;
	int i;
	struct sched_param param;
	int maxprio;
	maxprio=sched_get_priority_max(2);
	if (maxprio==-1) {
		perror("sched_get_priority_max error!\n");
		exit(1);
	}
	param.sched_priority=maxprio;
	if (sched_setscheduler(getpid(),2,&param)==-1) { 
		perror("sched_setscheduler() error!\n");
		exit(1);
	}
	start = clock();
	for (i = 0; i < COUNT; ++i) test_func();
	//printf("%lld\n", result);
	end = clock();
	double duration = (double)(end - start) / CLOCKS_PER_SEC;
	printf("%f seconds!\n", duration);
	return 0;
}