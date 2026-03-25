#include <stdio.h>

int main() {
    int a = 2;  // base
    int b = 3;  // exposant
    int resultat = 1;

    // Calcul de a^b
    for (int i = 0; i < b; i++) {
        resultat = resultat * a;
    }

    // Affichage du résultat
    printf("Le resultat de %d^%d est : %d\n", a, b, resultat);

    return 0;
}
