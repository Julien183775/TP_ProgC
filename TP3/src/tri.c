#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int tab[100];
    int i, j, temp;

    srand(time(NULL));

    // Remplissage du tableau
    for(i = 0; i < 100; i++) {
        tab[i] = rand() % 1000 + 1;
    }

    // Affichage avant tri
    printf("Tableau non trié :\n");
    for(i = 0; i < 100; i++) {
        printf("%d ", tab[i]);
    }
    printf("\n\n");

    // TRI À BULLES
    for(i = 0; i < 99; i++) {
        for(j = 0; j < 99 - i; j++) {
            if(tab[j] > tab[j + 1]) {
                temp = tab[j];
                tab[j] = tab[j + 1];
                tab[j + 1] = temp;
            }
        }
    }

    // Affichage après tri
    printf("Tableau trié :\n");
    for(i = 0; i < 100; i++) {
        printf("%d ", tab[i]);
    }
    printf("\n");

    return 0;
}
