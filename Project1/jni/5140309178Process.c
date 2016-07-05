/*
 *Author: Zhengtian XU
 *StudentID: 5140309178
 *Problem: generate process
 */
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void main(int argc, char* argv[])
{
	pid_t pid;
	printf("5140309178Parent: %d\n",getpid());
	pid = fork();
	if (pid<0)
	{
		fprintf(stderr, "Fork Failed\n");
		exit(-1);
	}
	else if (pid == 0)
	{
		printf("5140309178Child: %d\n",getpid());
		execl("/data/misc/test_ptree","100",NULL);
	}
	else
	{
		wait(NULL);
		exit(0);
	}
}
