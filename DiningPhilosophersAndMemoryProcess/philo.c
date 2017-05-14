#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

void* philoDiner(void *arg);

pthread_mutex_t forkss [1000];
int EatenPhilos = 0; 
int PhilAmount = 0; 
int numNom = 0; 

int main(int argc, char *argv[]) 
{
    pthread_t thread[1000];

    int thread_id[1000];
    int identify = 0;
    int result;
    int isLocked = 0;

    //Get number of philo and number of times to eat
    PhilAmount = atoi(argv[1]);
    numNom = atoi(argv[2]);

    //Create mutex/execute function
    for (int i = 0; i < PhilAmount; i++)
	{
        thread_id[i] = i;
        result = pthread_create(&(thread[i]), NULL, &philoDiner, &(thread_id[i]));
        pthread_mutex_init(&forkss[i], NULL);
    }


    //Join the threads
    for (int c = 0; c < PhilAmount; c++) 
	{
        result = pthread_join(thread[c], NULL);
    }
    //Kill the threads
    for (int c = 0; c < PhilAmount; c++) 
	{
        result = pthread_mutex_destroy(&forkss[c]);
    }


    return 0;
}

void* philoDiner(void *arg) {
    int minId = 0;
    int fatty = 0;
    int identify = *((int*) arg);
    minId = identify - 1;
    //Wrap around for begining and end
    if (minId == -1)
        minId = PhilAmount - 1;

    //For as many times as they have to eat
    while (fatty < numNom) {
        //Lock 1 and 2
        printf("Philosopher %d Thinking...\n", identify + 1);
        pthread_mutex_lock(&forkss[identify]);
        pthread_mutex_lock(&forkss[minId]);
        fatty++;
        sleep(1);
        //Unlock 1 and 2
        printf("Philosopher %d Eating....\n", identify + 1);
        pthread_mutex_unlock(&forkss[identify]);
        pthread_mutex_unlock(&forkss[minId]);
        printf("Philosopher %d has eaten!\n", identify + 1);

    }
    EatenPhilos++;
}