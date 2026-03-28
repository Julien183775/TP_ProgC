#include <stdio.h>

// Fonction récursive
int factorielle(int num) {
    if (num == 0) {
        return 1; // cas de base
    } else {
        return num * factorielle(num - 1);
    }
}

int main() {
    int n;

    // Tests avec différentes valeurs
    for (n = 0; n <= 5; n++) {
        printf("fact(%d) = %d\n", n, factorielle(n));
    }

    return 0;
}
