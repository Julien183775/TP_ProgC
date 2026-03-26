#include <stdio.h>
#include "operator.h"

void exo4_1() {
    int num1, num2, resultat;
    char op;

    printf("Entrez num1 : ");
    fflush(stdout);
    scanf("%d", &num1);

    printf("Entrez num2 : ");
    fflush(stdout);    
    scanf("%d", &num2);

    printf("Entrez l'operateur (+, -, *, /, %%, &, |, ~) : ");
    fflush(stdout);    
    scanf(" %c", &op); // espace important avant %c

    switch(op) {
        case '+':
            resultat = somme(num1, num2);
            break;
        case '-':
            resultat = difference(num1, num2);
            break;
        case '*':
            resultat = produit(num1, num2);
            break;
        case '/':
            resultat = quotient(num1, num2);
            break;
        case '%':
            resultat = modulo(num1, num2);
            break;
        case '&':
            resultat = et(num1, num2);
            break;
        case '|':
            resultat = ou(num1, num2);
            break;
        case '~':
            resultat = negation(num1); // un seul paramètre
            break;
        default:
            printf("Operateur invalide\n");
            return;
    }

    printf("Resultat : %d\n", resultat);

    return;
}
