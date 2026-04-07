#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t my_mutex = PTHREAD_MUTEX_INITIALIZER;

int cmp = 0;
double u;

void *calcul1(void *argument)
{
    while (1)
    {
        cmp++;
        pthread_mutex_lock(&my_mutex);

        u = (1.0 / 4.0) * (u - 1) * (u - 1);

        pthread_mutex_unlock(&my_mutex);
        printf("Thread1: %lf\n", u);

        sleep(rand() % 5 + 1);
    }
    pthread_exit(NULL);
}

void *calcul2(void *argument)
{
    while (1)
    {
        cmp++;
        pthread_mutex_lock(&my_mutex);

        u = (1.0 / 6.0) * (u - 2) * (u - 2);

        pthread_mutex_unlock(&my_mutex);
        printf("Thread2: %lf\n", u);

        sleep(rand() % 5 + 1);
    }
    pthread_exit(NULL);
}

int main()
{
    u = 1;
    pthread_t thread[2];
    pthread_create(&thread[0], NULL, calcul1, NULL);
    pthread_create(&thread[1], NULL, calcul2, NULL);
    pthread_join(thread[0], NULL);
    pthread_join(thread[1], NULL);
    return 0;
}
