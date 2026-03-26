#include <stdio.h>

int phrases_egales(const char *p1, const char *p2) {
    int i = 0;

    while (p1[i] != '\0' && p2[i] != '\0') {
        if (p1[i] != p2[i]) {
            return 0;
        }
        i++;
    }

    if (p1[i] == '\0' && p2[i] == '\0') {
        return 1;
    }

    return 0;
}

int main() {
    char *phrases[10] = {
        "Bonjour, comment ça va ?",
        "Le temps est magnifique aujourd'hui.",
        "C'est une belle journee.",
        "La programmation en C est amusante.",
        "Les tableaux en C sont puissants.",
        "Les pointeurs en C peuvent etre deroutants.",
        "Il fait beau dehors.",
        "La recherche dans un tableau est interessante.",
        "Les structures de donnees sont importantes.",
        "Programmer en C, c'est genial."
    };

    char recherche[200];
    int i;
    int trouve = 0;

    printf("Tableau de phrases :\n\n");
    for (i = 0; i < 10; i++) {
        printf("%d. %s\n", i + 1, phrases[i]);
    }

    printf("\nEntrez la phrase a rechercher : ");
    fflush(stdout);
    fgets(recherche, sizeof(recherche), stdin);

    i = 0;
    while (recherche[i] != '\0') {
        if (recherche[i] == '\n') {
            recherche[i] = '\0';
            break;
        }
        i++;
    }

    for (i = 0; i < 10; i++) {
        if (phrases_egales(phrases[i], recherche)) {
            trouve = 1;
            break;
        }
    }

    if (trouve) {
        printf("\nPhrase trouvee\n");
    } else {
        printf("\nPhrase non trouvee\n");
    }

    return 0;
}
