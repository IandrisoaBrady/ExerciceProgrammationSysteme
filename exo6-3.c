#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main()
{
    int fd = open("newArr_file.txt", O_RDWR | O_CREAT | O_TRUNC, 0664);
    int tab_t, *tab;

    printf("Entrez le nombre d'entier que vous voulsez entrer: ");
    scanf("%d", &tab_t);
    tab = malloc(tab_t * sizeof(int));

    printf("Entrez %d entiers: ", tab_t);
    for (int i = 0; i < tab_t; i++)
    {
        scanf("%d", &tab[i]);
    }

    write(fd, tab, sizeof(tab) * tab_t);
    
    free(tab);
    close(fd);
    return 0;
}