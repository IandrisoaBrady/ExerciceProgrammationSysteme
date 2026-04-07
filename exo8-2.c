#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>

#define BUFFER_SIZE 256

int cree_socket_tcp_ip()
{
    int sock;
    struct sockaddr_in adresse;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        fprintf(stderr, "Erreur socket\n");
        return -1;
    }

    memset(&adresse, 0, sizeof(struct sockaddr_in));

    adresse.sin_family = AF_INET;
    adresse.sin_port = htons(0);
    adresse.sin_addr.s_addr = htons(INADDR_ANY);

    if (bind(sock, (struct sockaddr *)&adresse,  sizeof(struct sockaddr_in)) < 0)
    {
        close(sock);
        fprintf(stderr, "Erreur bind\n");
        return -1;
    }
    return sock;
}

int affiche_adresse_socket(int sock)
{
    struct sockaddr_in adresse;
    socklen_t longueur;
    longueur = sizeof(struct sockaddr_in);

    if (getsockname(sock, (struct sockaddr *)&adresse, &longueur) < 0)
    {
        fprintf(stderr, "Erreur getsockname\n");
        return -1;
    }

    printf("IP = %s, Port = %u\n", inet_ntoa(adresse.sin_addr),  ntohs(adresse.sin_port));

    return 0;
}

void afficher_adresse_client(int sock_client)
{
    struct sockaddr_in addr_client;
    socklen_t addr_len = sizeof(addr_client);

    if (getpeername(sock_client, (struct sockaddr *)&addr_client, &addr_len) == 0)
    {
        char ip[16];
        strcpy(ip, inet_ntoa(addr_client.sin_addr));
        int port = ntohs(addr_client.sin_port);

        printf("Client connecté : IP = %s, Port = %d\n", ip, port);
    }
    else
    {
        perror("getpeername");
    }
}

void traiter_client(int sock_client)
{
    char buffer[BUFFER_SIZE];

    afficher_adresse_client(sock_client);

    char *message = "Bienvenue sur le serveur !\n";
    write(sock_client, message, strlen(message));

    int nb = read(sock_client, buffer, BUFFER_SIZE - 1);
    if (nb > 0)
    {
        buffer[nb] = '\0';
        printf("Message recu du client : %s", buffer);
    }

    char *reponse = "Message bien recu !\n";
    write(sock_client, reponse, strlen(reponse));

    close(sock_client);
}

int main(void)
{
    int sock_contact;
    int sock_connectee;
    struct sockaddr_in adresse, adresse_client;
    socklen_t longueur, client_len;
    pid_t pid_fils;

    sock_contact = cree_socket_tcp_ip();
    if (sock_contact < 0)
        return -1;

    listen(sock_contact, 5);
    printf("Mon adresse (sock contact) -> ");
    affiche_adresse_socket(sock_contact);
    printf("En attente de connexions...\n\n");

    while (1)
    {
        sock_connectee = accept(sock_contact, (struct sockaddr *)&adresse_client, &client_len);
        if (sock_connectee < 0)
        {
            perror("accept");
            continue;
        }

        pid_fils = fork();

        if (pid_fils == 0)
        {
            close(sock_contact);
            traiter_client(sock_connectee);
            close(sock_connectee);
            exit(0);
        }
        else if (pid_fils > 0)
        {
            close(sock_connectee);
            waitpid(-1, NULL, WNOHANG);
        }
        else
        {
            perror("fork");
            close(sock_connectee);
        }
    }

    close(sock_contact);

    return 0;
}