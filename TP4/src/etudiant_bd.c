#include <stdio.h>
#include <string.h>
#include "fichier.h"

// Définition de la structure
struct Etudiant {
    char nom[30];
    char prenom[30];
    char adresse[100];
    float note_prog;
    float note_sys;
};

int main() {
    struct Etudiant etudiants[5];
    char message[1000] = "";
    char ligne[200];

    // Saisie des 5 étudiants
    for (int i = 0; i < 5; i++) {
        printf("Entrez les details de l'etudiant.e %d :\n", i + 1);

        printf("Nom : ");
        fflush(stdout);
        scanf("%s", etudiants[i].nom);

        printf("Prenom : ");
        fflush(stdout);        
        scanf("%s", etudiants[i].prenom);

        printf("Adresse : ");
        fflush(stdout);        
        scanf(" %[^\n]", etudiants[i].adresse);

        printf("Note en programmation C : ");
        fflush(stdout);        
        scanf("%f", &etudiants[i].note_prog);

        printf("Note en systeme d'exploitation : ");
        fflush(stdout);        
        scanf("%f", &etudiants[i].note_sys);

        // Création d'une ligne pour le fichier
        sprintf(ligne, "%s %s %s %.2f %.2f\n",
                etudiants[i].nom,
                etudiants[i].prenom,
                etudiants[i].adresse,
                etudiants[i].note_prog,
                etudiants[i].note_sys);

        // Ajout au message global
        strcat(message, ligne);

        printf("\n");
    }

    // Ecriture dans le fichier
    ecrire_dans_fichier("etudiant.txt", message);

    // Lecture pour vérifier
    lire_fichier("etudiant.txt");

    return 0;
}
