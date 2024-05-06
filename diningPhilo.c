#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
//Ivin Mathew  19-04-2024
//Dining Philospher's problem
int N=5;
sem_t sticks[5];
void * philos(void * n){
	int i = *(int *) n;
	sem_wait(&sticks[i]);
	sem_wait(&sticks[(i+1)%N]);
	printf("Philosopher %d takes lstick\n",i);
	printf("Philosopher %d takes rstick\n\n",i);

	printf("%d is eating\n",i);
	sleep(2);

	printf("%d Finished eating\n",i);
	sem_post(&sticks[i]);
	sem_post(&sticks[(i+1)%N]);

	printf("Philosopher %d is thinking\n\n",i);
}
void main(){
	int arg[5];
	pthread_t t[5];
	for(int i=0;i<5;i++){
		sem_init(&sticks[i],0,1);
	}

	for(int i=0;i<5;i++){
		arg[i]=i;
		pthread_create(&t[i],NULL,philos,(void *)&arg[i]);

	}
	for(int i=0;i<5;i++)
		pthread_join(t[i],NULL);
}
