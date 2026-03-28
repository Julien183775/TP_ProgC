#include <stdio.h>
#include "liste.h"

void exo4_7() {
    printf("Exercice 4.7\n");

    struct liste_couleurs ma_liste;
    init_liste(&ma_liste);

    struct couleur c1 = {255, 0, 0, 255};
    struct couleur c2 = {0, 255, 0, 255};
    struct couleur c3 = {0, 0, 255, 255};

    insertion(&c1, &ma_liste);
    insertion(&c2, &ma_liste);
    insertion(&c3, &ma_liste);

    printf("Liste des couleurs :\n");
    parcours(&ma_liste);
}
