#include <stdio.h>

void exo4_1();
void exo4_2();
void exo4_7();  // nouveau

int main() {
    int choix;

    printf("Choisissez un exercice :\n");
    printf("1. Exercice 4.1\n");
    printf("2. Exercice 4.2\n");
    printf("3. Exercice 4.7\n");
    printf("Votre choix : ");
    scanf("%d", &choix);

    switch(choix) {
        case 1:
            exo4_1();
            break;
        case 2:
            exo4_2();
            break;
        case 3:
            exo4_7();
            break;
        default:
            printf("Choix invalide\n");
    }

    return 0;
}
