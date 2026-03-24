#include <stdio.h>

int main() {
    int somme = 0;

    // 1. Boucle pour parcourir les nombres de 1 à 1000
    for (int i = 1; i <= 1000; i++) {
        
        // 2b. Si divisible par 11, on ignore et on passe au suivant
        if (i % 11 == 0) {
            continue; // Passe directement à l'itération suivante de la boucle
        }

        // 2a. Si divisible par 5 ou par 7, on l'ajoute à la somme
        if (i % 5 == 0 || i % 7 == 0) {
            somme += i; // Équivaut à : somme = somme + i;
        }

        // 3. Si la somme dépasse 5000, on arrête tout
        if (somme > 5000) {
            break; // Sort immédiatement de la boucle for
        }
    }

    // 4. Affichage de la somme finale
    printf("La somme finale est : %d\n", somme);

    return 0;
}
