#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int tab[100];
    int i, j, temp;
    int nombre;
    int debut, fin, milieu;
    int trouve = 0;

    srand(time(NULL));

    for (i = 0; i < 100; i++) {
        tab[i] = rand() % 1000 + 1;
    }

    for (i = 0; i < 99; i++) {
        for (j = 0; j < 99 - i; j++) {
            if (tab[j] > tab[j + 1]) {
                temp = tab[j];
                tab[j] = tab[j + 1];
                tab[j + 1] = temp;
            }
        }
    }

    printf("Tableau trié :\n");
    for (i = 0; i < 100; i++) {
        printf("%d ", tab[i]);
    }

    printf("\n\nEntrez l'entier que vous souhaitez chercher : ");
    fflush(stdout);
    scanf("%d", &nombre);

    debut = 0;
    fin = 99;

    while (debut <= fin) {
        milieu = (debut + fin) / 2;

        if (tab[milieu] == nombre) {
            trouve = 1;
            break;
        } else if (nombre < tab[milieu]) {
            fin = milieu - 1;
        } else {
            debut = milieu + 1;
        }
    }

    if (trouve) {
        printf("Résultat : entier présent\n");
    } else {
        printf("Résultat : entier absent\n");
    }

    return 0;
}
