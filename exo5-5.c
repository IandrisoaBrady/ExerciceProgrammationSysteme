#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

pthread_mutex_t my_mutex = PTHREAD_MUTEX_INITIALIZER;
int compt = 0;

void *iterate(void *argument)
{
    while (1)
    {
        if (compt >= atoi((char *)argument))
        {
            exit(0);
        }
        pthread_mutex_lock(&my_mutex);
        compt++;
        pthread_mutex_unlock(&my_mutex);
        sleep(rand() % 5 + 1);
    }
    pthread_exit(NULL);
}

void *display(void *argument)
{
    while (1)
    {
        pthread_mutex_lock(&my_mutex);
        printf("Compteur: %d\n", compt);
        pthread_mutex_unlock(&my_mutex);
        sleep(2);
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    pthread_t thread[2];
    if (argv[1])
    {
        pthread_create(&thread[0], NULL, iterate, argv[1]);
        pthread_create(&thread[1], NULL, display, argv[1]);
        pthread_join(thread[0], NULL);
        pthread_join(thread[1], NULL);
    }
    else
    {
        printf("Arguments invalides\n");
    }
    return 0;
}