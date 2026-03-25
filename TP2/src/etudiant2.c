#include <stdio.h>
#include <string.h>

// Définition de la structure
struct Etudiant {
    char nom[30];
    char prenom[30];
    char adresse[100];
    float note_prog;
    float note_sys;
};

int main() {
    // Tableau de 5 étudiants
    struct Etudiant etudiants[5];

    // Initialisation avec strcpy
    strcpy(etudiants[0].nom, "Dupont");
    strcpy(etudiants[0].prenom, "Jean");
    strcpy(etudiants[0].adresse, "10, rue Naples");
    etudiants[0].note_prog = 14.5;
    etudiants[0].note_sys = 13.0;

    strcpy(etudiants[1].nom, "Martin");
    strcpy(etudiants[1].prenom, "Elodie");
    strcpy(etudiants[1].adresse, "8, rue de Londres");
    etudiants[1].note_prog = 12.0;
    etudiants[1].note_sys = 14.5;

    strcpy(etudiants[2].nom, "Hernandez");
    strcpy(etudiants[2].prenom, "Lucas");
    strcpy(etudiants[2].adresse, "15, rue de Paris");
    etudiants[2].note_prog = 16.5;
    etudiants[2].note_sys = 15.0;

    strcpy(etudiants[3].nom, "Lapierre");
    strcpy(etudiants[3].prenom, "Sylvie");
    strcpy(etudiants[3].adresse, "9, rue de Madrid");
    etudiants[3].note_prog = 11.0;
    etudiants[3].note_sys = 10.5;

    strcpy(etudiants[4].nom, "Renard");
    strcpy(etudiants[4].prenom, "Paul");
    strcpy(etudiants[4].adresse, "13, rue de Berlin");
    etudiants[4].note_prog = 15.0;
    etudiants[4].note_sys = 16.0;

    // Affichage
    for (int i = 0; i < 5; i++) {
        printf("Etudiant %d :\n", i + 1);
        printf("Nom : %s\n", etudiants[i].nom);
        printf("Prenom : %s\n", etudiants[i].prenom);
        printf("Adresse : %s\n", etudiants[i].adresse);
        printf("Note en programmation C : %.2f\n", etudiants[i].note_prog);
        printf("Note en systeme d'exploitation : %.2f\n", etudiants[i].note_sys);
        printf("-----------------------------\n");
    }

    return 0;
}
