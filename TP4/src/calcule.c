#include <stdio.h>
#include <stdlib.h>
#include "operator.h"

int main(int argc, char *argv[])
{
    char op;
    int a, b, resultat;

    // Vérification du nombre minimum d'arguments
    if (argc < 3)
    {
        printf("Usage : %s operateur nombre1 [nombre2]\n", argv[0]);
        return 1;
    }

    op = argv[1][0];
    a = atoi(argv[2]);

    switch (op)
    {
        case '~':
            resultat = negation(a);
            printf("Résultat : %d\n", resultat);
            break;

        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
        case '&':
        case '|':
            if (argc != 4)
            {
                printf("Erreur : cette opération nécessite deux nombres.\n");
                return 1;
            }

            b = atoi(argv[3]);

            switch (op)
            {
                case '+':
                    resultat = somme(a, b);
                    break;
                case '-':
                    resultat = difference(a, b);
                    break;
                case '*':
                    resultat = produit(a, b);
                    break;
                case '/':
                    if (b == 0)
                    {
                        printf("Erreur : division par zéro.\n");
                        return 1;
                    }
                    resultat = quotient(a, b);
                    break;
                case '%':
                    if (b == 0)
                    {
                        printf("Erreur : modulo par zéro.\n");
                        return 1;
                    }
                    resultat = modulo(a, b);
                    break;
                case '&':
                    resultat = et(a, b);
                    break;
                case '|':
                    resultat = ou(a, b);
                    break;
            }

            printf("Résultat : %d\n", resultat);
            break;

        default:
            printf("Opérateur invalide.\n");
            return 1;
    }

    return 0;
}
