#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int main()
{
    pid_t fils;
    switch (fils = fork())
    {
    case 0:
        while (1)
        {
            printf("Appuyez sur une touche:\n ");
            printf("'s' ou 'S': pour endormir le fils\n'r':pour redemarrer le fils\n'q' ou 'Q': pour tuer le fils\n");
            sleep(1);
            system("clear");
        }
        break;
    default:
        while (1)
        {
            switch (getchar())
            {
            case 's':
                case 'S':
                    kill(fils, SIGSTOP);
                    printf("Le processus fils a ete endormi\n");
                    break;
            case 'r':
                case 'R':
                    kill(fils, SIGCONT);
                    printf("Le processus fils a ete redemarrer\n");
                    break;
            case 'q':
                case 'Q':
                    kill(fils, SIGKILL);
                    printf("Le processus fils a ete tue\n");
                    exit(0);
                    break;
            default:
                printf("Le processus fils est encore en cours\n");
                sleep(2);
                break;
            }
        }
        break;
    }
    return 0;
}