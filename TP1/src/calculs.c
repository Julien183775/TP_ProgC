#include <stdio.h>

int main() {
    // 1. Déclaration et initialisation des variables
    // N'hésite pas à changer ces valeurs pour tester !
    int num1 = 12;
    int num2 = 5;
    char op = '+'; // Tu peux essayer avec '-', '*', '/', '%', '&', '|', '~'

    // 2. Structure switch pour choisir l'opération
    printf("Calcul demande : %d %c %d\n", num1, op, num2);
    
    switch (op) {
        case '+':
            printf("Resultat : %d\n", num1 + num2);
            break;
        case '-':
            printf("Resultat : %d\n", num1 - num2);
            break;
        case '*':
            printf("Resultat : %d\n", num1 * num2);
            break;
        case '/':
            // Sécurité : on vérifie que num2 n'est pas nul avant de diviser
            if (num2 != 0) {
                printf("Resultat : %d\n", num1 / num2);
            } else {
                printf("Erreur : Division par zero impossible.\n");
            }
            break;
        case '%':
            if (num2 != 0) {
                printf("Resultat : %d\n", num1 % num2);
            } else {
                printf("Erreur : Modulo par zero impossible.\n");
            }
            break;
        case '&':
            // Opérateur ET binaire (Bitwise AND)
            printf("Resultat : %d\n", num1 & num2);
            break;
        case '|':
            // Opérateur OU binaire (Bitwise OR)
            printf("Resultat : %d\n", num1 | num2);
            break;
        case '~':
            // Opérateur NON binaire (Bitwise NOT)
            // C'est un opérateur unaire, il s'applique à un seul nombre.
            printf("Resultat pour ~num1 (~%d) : %d\n", num1, ~num1);
            printf("Resultat pour ~num2 (~%d) : %d\n", num2, ~num2);
            break;
        default:
            // Si le caractère n'est pas dans la liste
            printf("Erreur : Operateur '%c' non reconnu.\n", op);
            break; // Pas strictement obligatoire à la fin, mais c'est une bonne pratique
    }

    return 0;
}
