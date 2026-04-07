#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

int main()
{
    pid_t fils[5];
    int curr_fils = 0;

    for (int i = 0; i < 5; i++)
    {
        fils[i] = fork();
        if (!fils[i])
        {
            while (1);
        }
    }

    printf("Appuyez sur une touche: \n");
    while (1)
    {
        switch (getchar())
        {
        case 's':
            case 'S':
                kill(fils[curr_fils], SIGSTOP);
                printf("Le processus fils[%d] a ete endormi\n", curr_fils);
                break;
        case 'r':
            case 'R':
                kill(fils[curr_fils], SIGCONT);
                printf("Le processus fils[%d] a ete redemarrer\n", curr_fils);
                break;
        case 'q':
            case 'Q':
                kill(fils[curr_fils], SIGKILL);
                printf("Le processus fils[%d] a ete tue\n", curr_fils);
                curr_fils++;
                break;
        default:
            printf("Le processus fils[%d] est encore en cours\n", curr_fils);
            printf("'s' ou 'S': pour endormir le fils\n'r':pour redemarrer le fils\n'q' ou 'Q': pour tuer le fils\n");
            break;
        }
        if (curr_fils == 5)
        {
            printf("Tous les processus ont ete tue\n");
            return 0;
        }
    }
}