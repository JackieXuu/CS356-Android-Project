/*
 *Author: Zhengtian XU
 *StudentID: 5140309178
 *Problem: Burger buddies problem
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
void *Cook(void *args);
void *Cashier(void *args);
void *Customer(void *args);
struct ID	/*The struct indicates the ID of each person*/
{
	pthread_t id;
};
unsigned int cooks, cashiers, customers, max_rack;
/*
 *cooks means the number of cooks
 *cashiers means the number of cashiers
 *customers means the number of customers
 *max_rack means the maxium volume of the rack
 */

sem_t empty_rack, free_C, burgers, customer_arrived, order;
/*
 *empty_rack is a semaphore which records the empty rack
 *free_C is a semaphore which records cashiers who are not busy
 *burgers is a semaphore which records the number of burgers which are available
 *customer_arrived is a semaphore which records the number of customers who are not served
 *order is a semaphore which shows customer post a order
 */
int main(int argc, char *argv[])
{
	srand(time(NULL));
	int argvCnt = 1, letters = 0;
	//Error detection
	if (argc != 5)
	{
		printf("Error! You should input 4 numbers, which is the number of cooks, cashiers, customers and max burgers\n");
		return -1;
	}
	while (argv[argvCnt])
	{
		letters = 0;
		while (argv[argvCnt][letters] != '\0')
		{
			if (argv[argvCnt][letters] < '0' || argv[argvCnt][letters] > '9')
			{
				printf("Error! You should input 4 numbers, which is the number of cooks, cashiers, customers and max burgers\n");
				return -1;
			}
			++letters;
		}
		++argvCnt;
	}

	pthread_t cook[100], cashier[100], customer[100];	
	struct ID cook_argv[100], cashier_argv[100], customer_argv[100];
	/*Read every parameters from the argv[]*/
	sscanf(argv[1], "%d", &cooks);
	sscanf(argv[2], "%d", &cashiers);
	sscanf(argv[3], "%d", &customers);
	sscanf(argv[4], "%d", &max_rack);
	/*Initialization of semaphore*/
	sem_init(&empty_rack, 0, max_rack);
	sem_init(&free_C, 0, cashiers);
	sem_init(&burgers, 0, 0);
	sem_init(&customer_arrived, 0, 0);
	sem_init(&order, 0, 0);

	printf("Cooks[%d], Cashiers[%d], Customers[%d]\n", cooks, cashiers, customers);
	printf("Begin run.\n");

	int i, rc;
	/* Start all cook threads */
	for (i = 0; i < cooks; ++i)
	{
		cook[i] = i + 1;
		cook_argv[i].id = i + 1;
		rc = pthread_create(&cook[i], NULL, Cook, &cook_argv[i]);
		if (rc)
		{
			printf("Error! Can't create cook pthread.\n");
			return EXIT_FAILURE;
		}
	}
	/* Start all cashier threads */
	for (i = 0; i < cashiers; ++i)
	{
		cashier[i] = i + cooks + 1;
		cashier_argv[i].id = i + 1;
		rc = pthread_create(&cashier[i], NULL, Cashier, &cashier_argv[i]);
		if (rc)
		{
			printf("Error! Can't create cashier pthread.\n");
			return EXIT_FAILURE;
		}
	}
	/* Start all customer threads */
	for (i = 0; i < customers; ++i)
	{
		customer[i] = i + cooks + cashiers + 1;
		customer_argv[i].id = i + 1;
		rc = pthread_create(&customer[i], NULL, Customer, &customer_argv[i]);
		if (rc)
		{
			printf("Error! Can't create customer pthread.\n");
			return EXIT_FAILURE;
		}
	}
	/*Waiting for all customers to be served.*/
	for(i = 0; i < customers; ++i)
	{
		rc = pthread_join(customer[i], NULL);
		if(rc)
		{
			printf("Error! Unable to join cutomer[%d]\n", i);
			return EXIT_FAILURE;
		}
	}
	/*Destroy semaphores*/
	sem_destroy(&empty_rack);
	sem_destroy(&free_C);
	sem_destroy(&burgers);
	sem_destroy(&customer_arrived);
	sem_destroy(&order);
	
	printf("Process end!\n");
	return 0;
}


void* Cook(void *args)
{
	/*Get thread id from args*/
	pthread_t id = (((struct ID*) (args)) -> id);	
	/* Infinite loop */
	while (1)
	{
		/*Check whether there has empty rack, if not, wait*/
		sem_wait(&empty_rack);	
		/*Cook*/					
		sleep(rand()%5);
		printf("Cook[%li] make a burger.\n", id);
		/*Produce a burger*/
		sem_post(&burgers);
	}
	return NULL;
}

void* Cashier(void *args)
{
	/*Get thread id from args*/
	pthread_t id = (((struct ID*) (args)) -> id);
	/* Infinite loop */
	while (1)
	{
		/*Wait for customer, if not, sleep*/
		sem_wait(&customer_arrived);
		/*Wait for customer to post a order*/
		sem_wait(&order);
		printf("Cashier[%li] accept an order.\n", id);
		/*Check whether there has a burger, if not, wait*/
		sleep(rand()%3);
		sem_wait(&burgers);
		printf("Cashier[%li] take a burger to customer\n", id);
		/*Take a burger*/
		sem_post(&empty_rack);
		/*Free a cashier*/
		sem_post(&free_C);
	}
	return NULL;
}

void* Customer(void *args)
{
	/*Get thread id from args*/
	pthread_t id = (((struct ID*) (args)) -> id);
	/*The arriving time is random*/
	sleep(rand()%15);
	/*Told cashier that a customer has been arrived*/
	sem_post(&customer_arrived);
	printf("Customer[%li] come.\n", id);
	/*Wait a free cashier*/
	sem_wait(&free_C);
	/*Time to order*/
	sleep(rand()%2);
	/*Post a order*/
	sem_post(&order);
	return NULL;
}

