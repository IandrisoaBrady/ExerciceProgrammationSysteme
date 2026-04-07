#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct TypeTableau
{
    int *tab;
    int tab_t;
    int x;
};

void *alloc_tab(void *argument_t)
{
    struct TypeTableau *func_tab = malloc(sizeof(struct TypeTableau));

    func_tab->tab_t = *((int *)argument_t);
    func_tab->tab = malloc(func_tab->tab_t * sizeof(int));

    for (int i = 0; i < func_tab->tab_t; i++)
    {
        func_tab->tab[i] = rand() % 100;
    }

    pthread_exit(func_tab);
}

void *find_x(void *argument)
{
    struct TypeTableau *func_tab = (struct TypeTableau *)argument;
    for (int i = 0; i < func_tab->tab_t; i++)
    {
        if (func_tab->x == func_tab->tab[i])
        {
            pthread_exit((void *)1);
        }
    }
    pthread_exit((void *)0);
}

int main()
{
    srand(time(NULL));

    pthread_t thread[2];
    int tab_t = 10, r_val, y;
    struct TypeTableau *new_tab;

    pthread_create(&thread[0], NULL, alloc_tab, &tab_t);
    pthread_join(thread[0], (void *)&new_tab);

    for (int i = 0; i < new_tab->tab_t; i++)
    {
        printf("%d ", new_tab->tab[i]);
    }

    printf("\nEntrez x: ");
    scanf("%d", &y);

    new_tab->x = y;

    pthread_create(&thread[1], NULL, find_x, new_tab);
    pthread_join(thread[1], (void *)&r_val);

    printf("r_val = %d\n", r_val);

    return 0;
}