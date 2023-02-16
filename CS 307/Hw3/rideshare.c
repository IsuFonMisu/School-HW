#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/wait.h>
#include <semaphore.h>

int waiting[2] = {0,0};

pthread_barrier_t barrier;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t printLock= PTHREAD_MUTEX_INITIALIZER;
sem_t sem[2];

void release(int t, int number){
	for (int i = 0; i<number;i++)
		sem_post(&sem[t]);
	waiting[t]-=number;
}

void* fan_thread(void* arg){

	int t = (intptr_t) arg;
	pthread_mutex_lock(&lock);

	int driver =0;
	printf("Thread ID: %lu, Team: %c, I am looking for a car\n",pthread_self(),'A'+t);

	if (waiting[t]==1){
		if (waiting[1-t]>=2){
			driver=1;
			release(t,1);
			release(1-t,2);
		}
		else{
			waiting[t]++;

			pthread_mutex_unlock(&lock);
			sem_wait(&sem[t]);
		}
	}
	else if(waiting[t]==3){
		driver=1;
		release(t,3);
	}
	else{
		waiting[t]++;
		pthread_mutex_unlock(&lock);
		sem_wait(&sem[t]);
	}
	pthread_mutex_lock(&printLock);
	printf("Thread ID: %lu, Team: %c, I have found a spot in a car\n",pthread_self(),'A'+t);
	pthread_mutex_unlock(&printLock);

	pthread_barrier_wait(&barrier);

	if(driver){
		printf("Thread ID: %lu, Team: %c, I am the captain and driving the car\n",pthread_self(),'A'+t);
		pthread_mutex_unlock(&lock);
	}
}


int main(int argc, char *argv[]) {
	if(argc!=3) {
		printf("The main terminates\n");
		return 0;
	}

	int A = atoi(argv[1]);
	int B = atoi(argv[2]);

	if (!((A+B)%4 || A%2 || B%2)) {
		long unsigned threads[A+B+1];

		pthread_barrier_init(&barrier,NULL,4);

		pthread_t t;

		for(int i = 0; i < A; i++)
			pthread_create(&threads[i], NULL,fan_thread,(void*) 0);

		for(int i = 0; i < B; i++)
			pthread_create(&threads[i+A], NULL,fan_thread,(void*) 1);

		for(int i = 0; i < A + B; i++)
			pthread_join(threads[i], NULL);
	}
	printf("The main terminates\n");
	return 0;
}
