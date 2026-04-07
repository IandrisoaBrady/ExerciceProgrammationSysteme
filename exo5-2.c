#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

void *alloc_tab(void *arguments)
{
    int tab_t = *((int *)arguments);
    int *arg_tab = malloc(tab_t * sizeof(int));

    for (int i = 0; i < tab_t; i++)
    {
        arg_tab[i] = rand() % 100;
    }

    pthread_exit(arg_tab);
}

int main()
{
    srand(time(NULL));

    pthread_t new_thread;
    int tab_t = 10;
    int *new_tab;

    pthread_create(&new_thread, NULL, alloc_tab, &tab_t);
    pthread_join(new_thread, (void *)&new_tab);

    for (int i = 0; i < tab_t; i++)
    {
        printf("tab %d : %d\n", i+1, new_tab[i]);
    }

    free(new_tab);
    return 0;
}