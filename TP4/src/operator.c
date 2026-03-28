#include "operator.h"

int somme(int a, int b) {
    return a + b;
}

int difference(int a, int b) {
    return a - b;
}

int produit(int a, int b) {
    return a * b;
}

int quotient(int a, int b) {
    if (b != 0)
        return a / b;
    else
        return 0; // éviter division par 0
}

int modulo(int a, int b) {
    if (b != 0)
        return a % b;
    else
        return 0;
}

int et(int a, int b) {
    return a & b;
}

int ou(int a, int b) {
    return a | b;
}

int negation(int a) {
    return ~a;
}
