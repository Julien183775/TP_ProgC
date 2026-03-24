#include <stdio.h>

int main() {
    // i. char
    // On peut stocker de petits nombres entiers ou des caractères.
    signed char s_char = -120;
    unsigned char u_char = 250;
    printf("signed char : %d\n", s_char);
    printf("unsigned char : %u\n\n", u_char);

    // ii. short
    signed short s_short = -30000;
    unsigned short u_short = 60000;
    printf("signed short : %hd\n", s_short);
    printf("unsigned short : %hu\n\n", u_short);

    // iii. int
    signed int s_int = -2000000000;
    unsigned int u_int = 4000000000U; // Le 'U' indique que c'est un unsigned
    printf("signed int : %d\n", s_int);
    printf("unsigned int : %u\n\n", u_int);

    // iv. long int
    signed long int s_long = -2000000000L; // Le 'L' indique que c'est un long
    unsigned long int u_long = 4000000000UL;
    printf("signed long int : %ld\n", s_long);
    printf("unsigned long int : %lu\n\n", u_long);

    // v. long long int
    signed long long int s_long_long = -9000000000000000000LL;
    unsigned long long int u_long_long = 18000000000000000000ULL;
    printf("signed long long int : %lld\n", s_long_long);
    printf("unsigned long long int : %llu\n\n", u_long_long);

    // vi. float (pas de version non-signée)
    float ma_float = 3.14159f; // Le 'f' indique que c'est un float et non un double
    printf("float : %f\n", ma_float);

    // vii. double (pas de version non-signée)
    double mon_double = 2.718281828;
    printf("double : %lf\n", mon_double);

    // viii. long double (pas de version non-signée)
    long double mon_long_double = 1.618033988749895L;
    printf("long double : %Lf\n", mon_long_double);

    return 0;
}
