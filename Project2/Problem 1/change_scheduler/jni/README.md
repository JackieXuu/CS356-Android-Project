		CS356 Operating System 
	Project 2: Android Scheduler
Name: Zhengtian Xu 		StudentID: 5140309178

--------------------------------------------------

Scheduler Changing:
	-change_scheduler.c 		| This program is used to change the scheduling policy of a specific process.

								| You can change every process' scheduling policy and its priority in  
								  this program.

								| This program has no parameters.

								| But in the execution you will be asked to enter 3 parameters.

								| 1. The first parameter is the pid of the process you want, you can find the 
									 pid of process through 'ps' command or 'ps -P' command.

								| 2. The second parameter is the scheduling policy. 0 means SCHED_NORMAL, 1 
								     means SCHED_FIFO and 2 means SCHED_RR.
								     
								| 3. The third parameter is the priority of the process, be sure to restrict 
									 your priority within a logical range.