#include <stdio.h>

int main() {
    // Initialisation des variables
    int a = 16;
    int b = 3;

    // 1. Addition
    printf("1. a + b = %d\n", a + b);

    // 2. Soustraction
    printf("2. a - b = %d\n", a - b);

    // 3. Multiplication
    printf("3. a * b = %d\n", a * b);

    // 4. Division (division entière car a et b sont des int)
    printf("4. a / b = %d\n", a / b);

    // 5. Modulo (reste de la division)
    // On utilise %% pour afficher le symbole % dans le printf
    printf("5. a %% b = %d\n", a % b);

    // 6. Égalité (0 = Faux, 1 = Vrai)
    printf("6. a est-il egal a b (a == b) ? %d\n", a == b);

    // 7. Supériorité (0 = Faux, 1 = Vrai)
    printf("7. a est-il superieur a b (a > b) ? %d\n", a > b);

    return 0;
}

