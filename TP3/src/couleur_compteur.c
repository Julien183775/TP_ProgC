#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} Couleur;

typedef struct {
    Couleur couleur;
    int compteur;
} CouleurComptee;

int couleurs_egales(Couleur c1, Couleur c2) {
    return (c1.r == c2.r &&
            c1.g == c2.g &&
            c1.b == c2.b &&
            c1.a == c2.a);
}

void afficher_couleur(Couleur c) {
    printf("0x%02x 0x%02x 0x%02x 0x%02x",
           c.r, c.g, c.b, c.a);
}

int main() {
    Couleur tableau[100];
    CouleurComptee distinctes[100];
    int nb_distinctes = 0;
    int i, j, trouve;

    srand(time(NULL));

    // Remplir le tableau avec des couleurs aléatoires
    for (i = 0; i < 100; i++) {
        tableau[i].r = rand() % 256;
        tableau[i].g = rand() % 256;
        tableau[i].b = rand() % 256;
        tableau[i].a = rand() % 256;
    }

    // Compter les couleurs distinctes
    for (i = 0; i < 100; i++) {
        trouve = 0;

        for (j = 0; j < nb_distinctes; j++) {
            if (couleurs_egales(tableau[i], distinctes[j].couleur)) {
                distinctes[j].compteur++;
                trouve = 1;
                break;
            }
        }

        if (!trouve) {
            distinctes[nb_distinctes].couleur = tableau[i];
            distinctes[nb_distinctes].compteur = 1;
            nb_distinctes++;
        }
    }

    // Affichage
    printf("Couleurs distinctes et nombre d'occurrences :\n\n");
    for (i = 0; i < nb_distinctes; i++) {
        afficher_couleur(distinctes[i].couleur);
        printf(" : %d\n", distinctes[i].compteur);
    }

    return 0;
}
