#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>

#define PORT 8888
#define BUFFER_SIZE 256
#define MAX_PRODUITS 100

typedef struct
{
    char nom[25];
    float prix;
} Produit;

Produit *product = NULL;
int nb_produits = 0;

int getNombreProduits()
{
    int cmp = 0;
    char fichier[] = "/tmp/produits.txt", buffer[256];

    FILE *fic = fopen(fichier, "r");
    if (!fic)
    {
        printf("%s: echec d'ouverture (get products count)\n", fichier);
        return -1;
    }

    while (fgets(buffer, 256, fic))
    {
        cmp++;
    }
    fclose(fic);
    return cmp;
}

void loadData()
{
    char fichier[] = "/tmp/produits.txt", ligne[256];
    int i = 0;

    FILE *fic = fopen(fichier, "r");
    if (!fic)
    {
        printf("%s: echec d'ouverture (load data)\n", fichier);
        exit(1);
    }

    while (fgets(ligne, sizeof(ligne), fic))
    {
        ligne[strcspn(ligne, "\n")] = '\0';

        char *nom = strtok(ligne, ":");
        char *prix = strtok(NULL, ":");

        if (nom && prix)
        {
            strcpy(product[i].nom, nom);
            product[i].prix = atof(prix);
            i++;
        }
    }
    fclose(fic);
}

void displayProduitInfo(Produit p)
{
    printf("\tNom : %s\n\tPrix : %.2f\n", p.nom, p.prix);
}

void displayProduits()
{
    for (int i = 0; i < nb_produits; i++)
    {
        printf("Produit %d : \n", i + 1);
        displayProduitInfo(product[i]);
        if (i != nb_produits - 1)
            printf("\n");
    }
}

Produit *findProduit(const char nom[25])
{
    for (int i = 0; i < nb_produits; i++)
    {
        if (strcmp(product[i].nom, nom) == 0)
        {
            return &product[i];
        }
    }
    return NULL;
}

int main()
{
    char nom[25];

    nb_produits = getNombreProduits();
    if (nb_produits <= 0)
    {
        printf("Aucun produit trouve ou fichier inexistant\n");
        return 1;
    }

    product = malloc(nb_produits * sizeof(Produit));
    if (!product)
    {
        printf("Erreur d'allocation memoire\n");
        return 1;
    }

    loadData();

    printf("=== Liste des produits ===\n");
    displayProduits();

    printf("\nEntrez un nom de produit : ");
    scanf("%24s", nom);

    Produit *p = findProduit(nom);

    if (p != NULL)
    {
        printf("\nProduit trouve :\n");
        displayProduitInfo(*p);
    }
    else
    {
        printf("\nProduit \"%s\" non trouve !\n", nom);
    }

    free(product);

    return 0;
}