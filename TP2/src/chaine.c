#include <stdio.h>

int main() {
    char chaine1[100], chaine2[100], copie[100], concat[200];
    int i = 0, longueur = 0;

    // Saisie des chaînes
    printf("Entrez la première chaine : ");
    fflush(stdout);
    scanf("%s", chaine1);

    printf("Entrez la deuxième chaine : ");
    fflush(stdout);
    scanf("%s", chaine2);

    printf("\n");

    // 1. Calcul de la longueur de chaine1
    i = 0;
    while (chaine1[i] != '\0') {
        longueur++;
        i++;
    }

    printf("Longueur de la premiere chaine : %d\n", longueur);

    // 2. Copie de chaine1 dans copie
    i = 0;
    while (chaine1[i] != '\0') {
        copie[i] = chaine1[i];
        i++;
    }
    copie[i] = '\0';

    printf("Copie : %s\n", copie);

    // 3. Concaténation chaine1 + chaine2
    i = 0;

    // Copier chaine1 dans concat
    while (chaine1[i] != '\0') {
        concat[i] = chaine1[i];
        i++;
    }

    int j = 0;

    // Ajouter chaine2
    while (chaine2[j] != '\0') {
        concat[i] = chaine2[j];
        i++;
        j++;
    }

    concat[i] = '\0';

    printf("Concatenation : %s\n", concat);

    return 0;
}
