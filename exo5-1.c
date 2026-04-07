#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// int pthread_create(pthread_t *thread, pthread_attr_t *attributs,void * (*fonction)(void *arg), void *arg);

struct Thread_arr
{
    int *arr;
    int arr_t;
};

void *afficherTableau(void *f_args)
{
    struct Thread_arr *s_args = (struct Thread_arr *)f_args;
    for (int i = 0; i < s_args->arr_t; i++)
    {
        printf("%d\n", s_args->arr[i]);
    }
    free(s_args->arr);
    pthread_exit(NULL);
}

int main()
{
    pthread_t new_thread;
    struct Thread_arr new_arr;
    new_arr.arr_t = 5;
    new_arr.arr = malloc(new_arr.arr_t * sizeof(int));
    for (int i = 0; i < new_arr.arr_t; i++)
    {
        new_arr.arr[i] = i;
    }
    pthread_create(&new_thread, NULL, afficherTableau, &new_arr);
    pthread_join(new_thread, NULL);
    free(new_arr.arr);
    return 0;
}