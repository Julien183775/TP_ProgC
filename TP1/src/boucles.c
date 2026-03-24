#include <stdio.h>

int main() {
    // La variable compteur qui détermine la taille (doit être < 10)
    int compteur = 5; 

    // Vérification de la consigne (strictement inférieur à 10)
    if (compteur >= 10) {
        printf("Erreur : la variable compteur doit etre strictement inferieure a 10.\n");
        return 1; // On arrête le programme
    }

    // ==========================================
    // PREMIÈRE PARTIE : Avec des boucles FOR
    // ==========================================
    printf("--- Version avec boucles FOR ---\n");
    
    for (int ligne = 0; ligne < compteur; ligne++) {
        for (int colonne = 0; colonne <= ligne; colonne++) {
            // Si c'est la 1ère colonne, la dernière de la ligne, ou la dernière ligne
            if (colonne == 0 || colonne == ligne || ligne == compteur - 1) {
                printf("* ");
            } else {
                printf("# ");
            }
        }
        // Retour à la ligne après avoir affiché toutes les colonnes d'une ligne
        printf("\n"); 
    }

    printf("\n"); // Espace entre les deux versions

    // ==========================================
    // DEUXIÈME PARTIE : Avec des boucles WHILE
    // ==========================================
    printf("--- Version avec boucles WHILE ---\n");
    
    int i = 0;
    while (i < compteur) {
        int j = 0;
        while (j <= i) {
            if (j == 0 || j == i || i == compteur - 1) {
                printf("* ");
            } else {
                printf("# ");
            }
            j++; // On passe à la colonne suivante
        }
        printf("\n");
        i++; // On passe à la ligne suivante
    }

    return 0;
}
