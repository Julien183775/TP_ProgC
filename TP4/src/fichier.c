#include <stdio.h>
#include "fichier.h"

void lire_fichier(char nom_de_fichier[]) {
    FILE *fichier;
    int  caractere;

    fichier = fopen(nom_de_fichier, "r");

    if (fichier == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier %s\n", nom_de_fichier);
        return;
    }

    printf("Contenu du fichier %s :\n", nom_de_fichier);

    while ((caractere = fgetc(fichier)) != EOF) {
        printf("%c", caractere);
    }

    printf("\n");
    fclose(fichier);
}

void ecrire_dans_fichier(char nom_de_fichier[], char message[]) {
    FILE *fichier;

    fichier = fopen(nom_de_fichier, "w");

    if (fichier == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier %s\n", nom_de_fichier);
        return;
    }

    fprintf(fichier, "%s", message);
    fclose(fichier);

    printf("Le message a ete ecrit dans le fichier %s.\n", nom_de_fichier);
}
