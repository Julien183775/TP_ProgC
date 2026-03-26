#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int tab[100];
    int i, nombre;
    int trouve = 0;

    srand(time(NULL));

    // Remplir le tableau
    for(i = 0; i < 100; i++) {
        tab[i] = rand() % 1000 + 1;
    }

    // Afficher le tableau
    printf("Tableau :\n");
    for(i = 0; i < 100; i++) {
        printf("%d ", tab[i]);
    }
    printf("\n");

    // Demander un nombre
    printf("Entrez l'entier que vous souhaitez chercher : ");
    scanf("%d", &nombre);

    // Recherche (linéaire)
    for(i = 0; i < 100; i++) {
        if(tab[i] == nombre) {
            trouve = 1;
            break;
        }
    }

    // Résultat
    if(trouve) {
        printf("Résultat : entier présent\n");
    } else {
        printf("Résultat : entier absent\n");
    }

    return 0;
}
