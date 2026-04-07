#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main(void)
{
    pid_t pid_fils;
    int status;
    switch (pid_fils=fork())
    {
        case -1 :
            perror("Problème dans fork()\n");
            exit(errno);
            break;
        
        case 0 :
            puts("Je suis le fils");
            exit(5);
        
        default : 
            puts("Je suis le père");
            wait(&status); //wait(NULL)
            break;
    }
    return 0;
}