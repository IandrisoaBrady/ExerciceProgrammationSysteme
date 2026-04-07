#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int n, i;
    printf("Entrez n: ");
    scanf("%d", &n);

    int *tab = malloc(n * sizeof(int));
    printf("Entrez les valeurs dans tab: \n");

    for (int j = 0; j < n; j++)
    {
        scanf("%d", &tab[j]);
    }

    do
    {
        printf("Entrez i: ");
        scanf("%d", &i);

        if (i < 0 || i >= n)
        {
            printf("Cela entrainera une erreur de segmentation\n");
        }
    } while (i < 0 || i >= n);

    printf("%d\n", tab[i]);
    free(tab);
}