#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main(void)
{
    pid_t pid_fils;
    for(int i=1;i<=5;i++)
    {
        switch (pid_fils=fork())
        {
            case -1 :
                perror("Problème dans fork()\n");
                exit(errno);
                break;
        
            case 0 :
                exit(i+4);
                break;
        
            default : 
                wait(NULL);
                break;
        }
    }
    return 0;
}