#include <stdio.h>

void afficher_binaire(int n) {

    int started = 0; // pour éviter les zéros au début

    for (int i = 31; i >= 0; i--) {
        int bit = (n >> i) & 1;

        if (bit == 1) {
            started = 1;
        }

        if (started) {
            printf("%d", bit);
        }
    }

    if (!started) {
        printf("0");
    }
}

int main() {

    int nombres[] = {0, 4096, 65536, 65535, 1024};
    int taille = 5;

    for (int i = 0; i < taille; i++) {
        printf("%d en binaire : ", nombres[i]);
        afficher_binaire(nombres[i]);
        printf("\n");
    }

    return 0;
}
