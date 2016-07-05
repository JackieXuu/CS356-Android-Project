		CS356 Operating System 
	Project 2: Android Scheduler
Name: Zhengtian Xu 		StudentID: 5140309178

--------------------------------------------------

Modify Scheduler:
	-fork.c 			| The first prolblem asks us to modify the default scheduling policy 
						  of all the descendants of zygote from SCHED_NORMAL to SCHED_RR and 
						  set its priority to (mαx priority of SCHED_RR )/5*(PID mod 5) + 1.

						| To implement this program, I modify some codes in fork.c.
						  In line 1676, I add the following codes:
						  ******************************************************************
						  	if (strcmp(p->parent->comm,"main")==0) {
								p->policy=SCHED_RR;
								p->rt_priority=99/5*(p->pid % 5)+1;
								p->normal_prio=MAX_RT_PRIO-1 - p->rt_priority;
								p->prio=rt_mutex_getprio(p);
								printk("sched fork pid:%d, name:%s, prio:%d, rt_prio:%d\n",p->pid, p->comm, p->
								prio, p->rt_priority);
							}
							else printk("other fork pid:%d, name:%s, prio:%d, rt_prio:%d\n",p->pid, p->comm, p->
							prio, p->rt_priority);

							if (rt_prio(p->prio))
								p->sched_class=&rt_sched_class;
						  ******************************************************************

	-rt.c 				| The second problem asks us to change the CPU picking policy from
						  default picking to randomly picking.

						| To implement this program, I modify some codes  in rt.c
						  In line 1329, I add the following codes:
						  ******************************************************************
						  	static struct sched_rt_entity *pick_next_rt_entity(struct rq *rq,
						   struct rt_rq *rt_rq)
							{
								struct rt_prio_array *array = &rt_rq->active;
								struct sched_rt_entity *next = NULL;
								struct list_head *queue;
								unsigned int randNum;
								int idx;
								int next_task[MAX_RT_PRIO] = {0};
								int next_task_num = 0;

								int i = 0;	
								while (i < MAX_RT_PRIO)
								{
									if (!list_empty(array->queue+i))
									{
										next_task[next_task_num++] = i;
										printk("Stored: %d\n", i);
									}
									++i;
								}
								get_random_bytes(&randNum, sizeof(int));
								randNum = randNum % next_task_num;
								idx = next_task[randNum];
								BUG_ON(idx >= MAX_RT_PRIO);

								printk("Pick: %d\n", idx);

								queue = array->queue + idx;
								next = list_entry(queue->next, struct sched_rt_entity, run_list);

								return next;
							}
						  ******************************************************************
