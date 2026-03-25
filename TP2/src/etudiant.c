#include <stdio.h>

int main() {
    char noms[5][30] = {
        "Dupont",
        "Martin",
        "Hernandez",
        "Lapierre",
        "Renard"
    };

    char prenoms[5][30] = {
        "Jean",
        "Elodie",
        "Lucas",
        "Sylvie",
        "Paul"
    };

    char adresses[5][100] = {
        "12 rue de Paris",
        "8 avenue Victor Hugo",
        "25 boulevard National",
        "3 rue des Fleurs",
        "18 place de la Republique"
    };

    float notes_prog[5] = {14.5, 12.0, 16.5, 11.0, 15.0};
    float notes_sys[5]  = {13.0, 14.5, 15.0, 10.5, 16.0};

    for (int i = 0; i < 5; i++) {
        printf("Etudiant %d :\n", i + 1);
        printf("Nom : %s\n", *(noms + i));
        printf("Prenom : %s\n", *(prenoms + i));
        printf("Adresse : %s\n", *(adresses + i));
        printf("Note en programmation C : %.2f\n", *(notes_prog + i));
        printf("Note en systeme d'exploitation : %.2f\n", *(notes_sys + i));
        printf("-----------------------------\n");
    }

    return 0;
}
