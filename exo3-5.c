#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    char file[200];
    while (1)
    {
        printf("Entrez un nom de fichier: ");
        scanf("%s", file);
        if (file)
        {
            int fils = fork();
            if (fils == 0)
                execl("/usr/bin/emacs", "emacs", file, NULL);
        }
        printf("\n");
    }
}