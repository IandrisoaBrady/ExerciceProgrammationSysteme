#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t my_mutex = PTHREAD_MUTEX_INITIALIZER;

int N = 100;
double *tab;

void *moy_tab(void *argumrnt)
{
    for (int i = 1; i < 99; i++)
    {
        pthread_mutex_lock(&my_mutex);
        tab[i] = (tab[i - 1] + tab[i] + tab[i + 1]) / 3;
        pthread_mutex_unlock(&my_mutex);
        sleep(rand() % 3 + 1);
    }

    pthread_exit(NULL);
}

void *afficher(void *argumrnt)
{
    while (1)
    {
        pthread_mutex_lock(&my_mutex);

        for (int i = 0; i < 100; i++)
        {
            printf("%.2lf ", tab[i]);
        }
        
        pthread_mutex_unlock(&my_mutex);
        sleep(4);
    }
    pthread_exit(NULL);
}

int main()
{
    srand(time(NULL));
    pthread_t thread[2];

    tab = malloc(N * sizeof(double));
    tab[0] = tab[99] = 0;

    for (int i = 1; i < 99; i++)
    {
        tab[i] = rand() % 101;
    }
    
    pthread_create(&thread[0], NULL, moy_tab, NULL);
    pthread_create(&thread[1], NULL, afficher, NULL);
    pthread_join(thread[0], NULL);
    pthread_join(thread[1], NULL);
    return 0;
}