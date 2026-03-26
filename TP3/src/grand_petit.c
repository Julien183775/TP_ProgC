#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int tab[100];
    int i;

    // Initialiser le générateur aléatoire
    srand(time(NULL));

    // Remplir le tableau avec des valeurs aléatoires entre 1 et 1000
    for(i = 0; i < 100; i++) {
        tab[i] = rand() % 1000 + 1;
    }

    // Initialisation min et max avec la première valeur
    int min = tab[0];
    int max = tab[0];

    // Parcours du tableau
    for(i = 1; i < 100; i++) {
        if(tab[i] < min) {
            min = tab[i];
        }
        if(tab[i] > max) {
            max = tab[i];
        }
    }

    // Affichage
    printf("Le numéro le plus grand est : %d\n", max);
    printf("Le numéro le plus petit est : %d\n", min);

    return 0;
}
