#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10

int main() {
    int tab_int[N];
    float tab_float[N];

    int *p_int = tab_int;
    float *p_float = tab_float;

    srand(time(NULL));

    /* Remplissage des tableaux avec des valeurs aléatoires */
    for (int i = 0; i < N; i++) {
        *(p_int + i) = rand() % 100;                 // entier entre 0 et 99
        *(p_float + i) = (float)(rand() % 100) / 10; // float entre 0.0 et 9.9
    }

    /* Affichage AVANT */
    printf("Tableau d'entiers (avant) :\n");
    for (int i = 0; i < N; i++) {
        printf("%d ", *(p_int + i));
    }

    printf("\n\nTableau de floats (avant) :\n");
    for (int i = 0; i < N; i++) {
        printf("%.2f ", *(p_float + i));
    }

    /* Multiplication par 3 si indice divisible par 2 */
    for (int i = 0; i < N; i++) {
        if (i % 2 == 0) {
            *(p_int + i) *= 3;
            *(p_float + i) *= 3;
        }
    }

    /* Affichage APRES */
    printf("\n\nTableau d'entiers (apres) :\n");
    for (int i = 0; i < N; i++) {
        printf("%d ", *(p_int + i));
    }

    printf("\n\nTableau de floats (apres) :\n");
    for (int i = 0; i < N; i++) {
        printf("%.2f ", *(p_float + i));
    }

    printf("\n");

    return 0;
}
