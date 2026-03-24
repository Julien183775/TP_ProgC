#include <stdio.h>

int main() {
    int n = 5;
    int i, j;

    for (i = 1; i <= n; i++) {

        // Espaces
        for (j = 1; j <= n - i; j++) {
            printf(" ");
        }

        // Partie croissante
        for (j = 1; j <= i; j++) {
            printf("%d", j);
        }

        // Partie décroissante
        for (j = i - 1; j >= 1; j--) {
            printf("%d", j);
        }

        printf("\n");
    }

    printf("Generation de la pyramide terminee.\n");

    return 0;
}
