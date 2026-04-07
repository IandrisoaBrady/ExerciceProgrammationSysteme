#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int a;
    switch (argc)
    {
        case 3:
            a=atoi(argv[1]) + atoi(argv[2]);
            printf("\n%s + %s = %d\n",argv[1],argv[2],a);
            break;
    
        default:
            printf("Veuillez entrez deux arguments entiers pour lancer le programme\n");
            exit(0);
            break;
    }
    return 0;
}