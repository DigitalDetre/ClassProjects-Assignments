// Phong Nguyenho - ph094398
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

#define PHILOSOPHERS 5

pthread_mutex_t forks[PHILOSOPHERS];
pthread_t phil[PHILOSOPHERS];
pthread_attr_t attr[PHILOSOPHERS];

// Makes the philoisophers wait
void thinking(int philosopher_number) 
{
	printf("Philosopher %d is thinking\n", philosopher_number);
	sleep(rand() % 3 + 1);
}

// Makes the philoisophers wait
void eating(int philosopher_number) 
{
	printf("Philosopher %d is eating\n", philosopher_number);
	sleep(rand() % 3 + 1);
}

// Makes the philosophers pick up a fork
void pickup_forks(int philosopher_number) 
{
	printf("Philosopher %d is waiting to pick up a fork\n", philosopher_number);
	pthread_mutex_lock(&forks[(philosopher_number + PHILOSOPHERS) % PHILOSOPHERS]);
	printf("Philosopher %d has picked up a fork \n", philosopher_number);
}

// Makes the philosophers return the forks
void return_forks(int philosopher_number)
{
	printf("Philosopher %d is returning the fork\n", philosopher_number);
	pthread_mutex_unlock(&forks[(philosopher_number + PHILOSOPHERS) % PHILOSOPHERS]);
}

// Operates the philosophers
void *philosopher(int philosopher_number) 
{
	int timer = 10;
	while (timer > 0) 
	{
		thinking(philosopher_number);
		pickup_forks(philosopher_number);
		eating(philosopher_number);
		return_forks(philosopher_number);
		timer--;
	}
}

// Initializes the philosophers
int main(void)
{
	int i;
	srand(time(NULL));
	for (i = 0; i < PHILOSOPHERS; i++) 
		pthread_mutex_init(&forks[i], NULL);
	
	for (i = 0; i < PHILOSOPHERS; i++) 
		pthread_attr_init(&attr[i]);
	
	for (i = 0; i < PHILOSOPHERS; i++) 
		pthread_create(&phil[i], &attr[i], philosopher, (void *)(i));

	for (i = 0; i < PHILOSOPHERS; i++) 
		pthread_join(phil[i], NULL);

	return 0;
}
