#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
    __pid_t fils;
    char *file_path = "summary.c";
    FILE *file = fopen(file_path, "r");
    int tube[2], res[2];
    pipe(tube);
    pipe(res);
    char response[64], word[64], command[256];
    switch (fils = fork())
    {
    case -1:
        printf("Erreur lors de la création du fils");
        break;
    case 0:
        close(tube[0]);
        printf("Entrez le mot: ");
        scanf("%s", word);
        write(tube[1], word, strlen(word));
        int value;
        close(res[1]);
        read(res[0], &value, sizeof(int));
        printf("Value: %d\n", value);
        break;
    default:
        close(tube[1]);
        dup2(tube[0], STDOUT_FILENO);
        fgets(response, 64, stdout);
        printf("%s", response);
        exit(0);
        sprintf(command, "grep %s %s > /dev/null", response, file_path);
        int value2;
        if (!system(command))
        {
            value2 = 1;
        }
        else
        {
            value2 = 0;
        }
        close(res[0]);
        write(res[1], &value2, sizeof(int));
        break;
    }
}