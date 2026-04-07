#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

pid_t pid_fils1;
pid_t pid_fils2;

pid_t suivant(pid_t fils2)
{
    switch (pid_fils2=fork())
    {
        case -1 :
            perror("Problème dans fork() pour fils 2\n");
            exit(errno);
            break;
        
        case 0 :
            puts("Je suis le fils 2");
            exit(6);
        
        default :
            puts("Je suis le père");
            wait(NULL); 
            break;
    }
    return fils2;
}
int main(void)
{
    switch (pid_fils1=fork())
    {
        case -1 :
            perror("Problème dans fork() pour fils 1\n");
            exit(errno);
            break;
        
        case 0 :
            puts("Je suis le fils 1");
            exit(5);
        
        default : 
            suivant(pid_fils2);
            wait(NULL); 
            break;
    }
    return 0;
}