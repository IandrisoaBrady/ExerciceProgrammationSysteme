#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    switch(argc)
    {
        char chaine[200];
        case 2:
            sprintf(chaine,"cp %s .",argv[2]);
            system(chaine);
            break;
        default:
            exit(0);
    }
    return 0;
}