#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    if (argv[1])
    {
        DIR *dir;
        dir = opendir(argv[1]);

        struct dirent *dir_ent;

        while ((dir_ent = readdir(dir)) != NULL)
        {
            struct stat st;
            char *nom = malloc(1024 * sizeof(char));

            sprintf(nom, "%s/%s", argv[1], dir_ent->d_name);
            stat(nom, &st);

            if (S_ISREG(st.st_mode) && st.st_size >= 1000000)
            {
                printf("%s\n", dir_ent->d_name);
            }
            free(nom);
        }
    }
    return 0;
}