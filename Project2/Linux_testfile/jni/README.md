		CS356 Operating System 
	Project 2: Android Scheduler
Name: Zhengtian Xu 		StudentID: 5140309178

--------------------------------------------------

Linux test file:
	These program is used to compete with android application.

	These files realize the function that it execute many addition.

	Always we call them time cost processes.

	What they print is the execution time of themselves.

	-test_file.c 			| 1 or 2 parameters which respectively represents scheduling policy and priority.
							  If enter only one parameter, the default priority is the maximal priority.

	-test_file_NORMAL		| no parameter, with SCHED_NORMAL and its priority is 0.

	-test_file_FIFO 		| no parameter, with SCHED_FIFO and its priority is 99.
	
	-test_file_RR 			| no parameter, with SCHED_RR and its priority is 99.
