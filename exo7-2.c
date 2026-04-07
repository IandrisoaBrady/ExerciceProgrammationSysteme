#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main()
{
    int num = 0;
    char buffer[256];

    printf("Entrez un entier: ");
    scanf("%d", &num);

    int fd = open("/tmp/entier.txt", O_RDWR | O_TRUNC | O_CREAT, 0644);
    int num_t = sprintf(buffer, "%d", num);
    
    write(fd, buffer, num_t);
}