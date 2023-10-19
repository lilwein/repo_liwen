#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>

#include <semaphore.h>
#include "performance.h"

#define N 1000 // number of threads
#define M 10000 // number of iterations per thread
#define V 1 // value added to the balance by each thread at each iteration

unsigned long int shared_variable;
int n = N, m = M, v = V;

sem_t sem;

void* thread_work(void *arg) {
	int i;
	for (i = 0; i < m; i++){
		sem_wait(&sem);
		shared_variable += v;
		sem_post(&sem);
	}
	return NULL;
}

int main(int argc, char **argv)
{
	if (argc > 1) n = atoi(argv[1]);
	if (argc > 2) m = atoi(argv[2]);
	if (argc > 3) v = atoi(argv[3]);
	
	shared_variable = 0;

	timer t;

	if(sem_init(&sem,0,1)==-1){
		exit(EXIT_FAILURE);
	}


	printf("Going to start %d threads, each adding %d times %d to a shared variable initialized to zero...", n, m, v); fflush(stdout);
	pthread_t* threads = (pthread_t*)malloc(n * sizeof(pthread_t));
	int i;

	begin(&t);

	for (i = 0; i < n; i++)
		if (pthread_create(&threads[i], NULL, thread_work, NULL) != 0) {
			fprintf(stderr, "Can't create a new thread, error %d\n", errno);
			exit(EXIT_FAILURE);
		}
	printf("ok\n");

	printf("Waiting for the termination of all the %d threads...", n); fflush(stdout);
	for (i = 0; i < n; i++)
		pthread_join(threads[i], NULL);
	
	end(&t);
	printf("ok\n");

	unsigned long int expected_value = (unsigned long int)n*m*v;
	printf("The value of the shared variable is %lu. It should have been %lu\n", shared_variable, expected_value);
	// if (expected_value > shared_variable) {
		unsigned long int lost_adds = (expected_value - shared_variable) / v;
		printf("Number of lost adds: %lu, %f%%\n", lost_adds, lost_adds/(double)expected_value);
	// }

	printf("Tempo impiegato: %lu ms\n\n", get_milliseconds(&t));

	sem_destroy(&sem);

    free(threads);

	return EXIT_SUCCESS;
}

