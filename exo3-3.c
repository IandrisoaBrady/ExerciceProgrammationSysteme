#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    switch(argc)
    {
        case 1:
            execl("/usr/bin/emacs","emacs",argv[1],NULL);
            break;
        default:
            printf("Relancez le programme avec un seul argument\n");
            exit(0);
    }
    return 0;
}