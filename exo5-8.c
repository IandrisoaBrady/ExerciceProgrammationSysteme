#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <time.h>

int t = 0;
sem_t sem;

void *iterate(void *argument)
{
    while (t < 10)
    {
        int start_time = time(NULL);
        int curr_thread = *((int *)argument);

        sem_wait(&sem);
        t++;
        sleep(curr_thread == 0 ? 2 : (rand() % (9 - 5)) + 4);

        int end_time = time(NULL);

        printf("Time %d\n", end_time - start_time);
        sem_post(&sem);
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t thread[2];
    sem_init(&sem, 0, 1);

    for (int i = 0; i < 2; i++)
    {
        pthread_create(&thread[i], NULL, iterate, &i);
    }

    for (int i = 0; i < 2; i++)
    {
        pthread_join(thread[i], NULL);
    }

    sem_destoy(&sem);
    return 0;
}