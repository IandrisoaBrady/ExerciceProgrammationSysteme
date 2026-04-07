#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

pid_t pid_fils;
int main(void)
{
    for(int i=1;i<=5;i++)
    {
        switch (pid_fils=fork())
        {
            case -1 :
                perror("Problème dans fork()\n");
                exit(errno);
                break;
        
            case 0 :
                printf("Je suis le fils %d\n",i);
                exit(i+4);
                break;
        
            default : 
                if(i==1)
                {
                    printf("Je suis le père\n");
                }
                wait(NULL);
                break;
        }
    }
    return 0;
}