/*
 *Author: Zhengtian XU
 *StudentID: 5140309178
 *Problem: test ptree
 */

#include <stdio.h>
#include "/home/gerald/kernel/goldfish/include/linux/prinfo.h"
#include <stdlib.h>
#include <ctype.h>
#define DEFAULT_NUM 100
void print(struct prinfo* buf, int nr);

int main(int argc, char** argv)
{
	struct prinfo* buf;
	int nr;
	int result = 0;
	int flag = 1;
	/* No parameter input */
	if (argc <= 1)											
		nr = DEFAULT_NUM;
	/* Change the input into vaild digit number */
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
	return 0;
}

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
		printf("%s,%d,%ld,%d,%d,%d,%ld\n", buf[i].comm, buf[i].pid, buf[i].state,
					buf[i].parent_pid, buf[i].first_child_pid, buf[i].next_sibling_pid, buf[i].uid);
		++cnt;
		matrix[cnt] = buf[i].pid;
	}
}
