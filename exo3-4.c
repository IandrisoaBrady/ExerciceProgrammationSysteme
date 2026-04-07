#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    char dir[200], command[256];
    while (1)
    {
        printf("Entrez un nom de repértoire: ");
        scanf("%s", dir);
        if (dir)
        {
            sprintf(command, "install -D ./* %s", dir);
            system(command);
        }
        printf("\n");
    }
    return 0;
}