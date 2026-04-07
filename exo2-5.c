#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <time.h>

pid_t pid_fils1;
pid_t pid_fils2;

pid_t suivant(pid_t fils2,int b)
{
    switch (pid_fils2=fork())
    {
        case -1 :
            perror("Problème dans fork() pour fils 2\n");
            exit(errno);
            break;
        
        case 0 :
            sleep(b);
            printf("fils 2 vient d'attendre %d\n",b);
            exit(6);
        
        default :
            //puts("Je suis le père");
            wait(NULL); 
            break;
    }
    return fils2;
}
int main(void)
{
    srand(time(NULL));
    int a = ( rand() % 10 ) + 1 ;
    int b = ( rand() % 10 ) + 1 ;
    int c=a+b;
    switch (pid_fils1=fork())
    {
        case -1 :
            perror("Problème dans fork() pour fils 1\n");
            exit(errno);
            break;
        
        case 0 :
            //puts("Je suis le fils 1");
            sleep(a);
            printf("fils 1 vient d'attendre %d\n",a);
            exit(5);
        
        default : 
            suivant(pid_fils2,b);
            wait(NULL); 
            break;
    }
    printf("duree totale = %d\n",c);
    return 0;
}