#include <stdio.h>
#include <stdlib.h>
#include "liste.h"

void init_liste(struct liste_couleurs *liste) {
    liste->tete = NULL;
}

void insertion(struct couleur *c, struct liste_couleurs *liste) {
    struct noeud *nouveau = malloc(sizeof(struct noeud));

    if (nouveau == NULL) {
        printf("Erreur d'allocation memoire\n");
        return;
    }

    nouveau->c = *c;
    nouveau->suivant = NULL;

    if (liste->tete == NULL) {
        liste->tete = nouveau;
    } else {
        struct noeud *courant = liste->tete;
        while (courant->suivant != NULL) {
            courant = courant->suivant;
        }
        courant->suivant = nouveau;
    }
}

void parcours(struct liste_couleurs *liste) {
    struct noeud *courant = liste->tete;
    int i = 1;

    while (courant != NULL) {
        printf("Couleur %d : R=%u G=%u B=%u A=%u\n",
               i,
               courant->c.r,
               courant->c.g,
               courant->c.b,
               courant->c.a);
        courant = courant->suivant;
        i++;
    }
}
