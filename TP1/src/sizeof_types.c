#include <stdio.h>

int main() {
    printf("Tailles des types de base (en octets) :\n");
    printf("---------------------------------------\n");

    // Types entiers
    printf("char : %lu\n", sizeof(char));
    printf("short : %lu\n", sizeof(short));
    printf("int : %lu\n", sizeof(int));
    printf("long int : %lu\n", sizeof(long int));
    printf("long long int : %lu\n", sizeof(long long int));

    // Types à virgule
    printf("float : %lu\n", sizeof(float));
    printf("double : %lu\n", sizeof(double));
    printf("long double : %lu\n", sizeof(long double));

    return 0;
}
