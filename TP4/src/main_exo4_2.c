#include <stdio.h>
#include <string.h>
#include "fichier.h"

void exo4_2() {
    int choix;
    char nom_de_fichier[100];
    char message[200];

    printf("Que souhaitez-vous faire ?\n");
    printf("1. Lire un fichier\n");
    printf("2. Ecrire dans un fichier\n");
    printf("Votre choix : ");
    fflush(stdout);
    scanf("%d", &choix);
    getchar();

    if (choix == 1) {
        printf("Entrez le nom du fichier a lire : ");
        fflush(stdout);
        scanf("%s", nom_de_fichier);

        lire_fichier(nom_de_fichier);
    }
    else if (choix == 2) {
        printf("Entrez le nom du fichier dans lequel vous souhaitez ecrire : ");
        fflush(stdout);
        scanf("%s", nom_de_fichier);
        getchar();

        printf("Entrez le message a ecrire : ");
        fflush(stdout);
        scanf(" %[^\n]", message);

        message[strcspn(message, "\n")] = '\0';

        ecrire_dans_fichier(nom_de_fichier, message);
    }
    else {
        printf("Choix invalide.\n");
    }

    return;
}
