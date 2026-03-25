#include <stdio.h>
#include <string.h>

int main(void) {
    /* 1. Déclaration et initialisation des variables */
    char c = 'A';
    short s = 256;
    int i = 0xA47865FF;
    long int li = 0x12345678;
    long long int lli = 0x1122334455667788LL;
    float f = 2.0f;
    double d = 2.0;
    long double ld = 2.0L;

    /* 2. Déclaration des pointeurs */
    char *pc = &c;
    short *ps = &s;
    int *pi = &i;
    long int *pli = &li;
    long long int *plli = &lli;
    float *pf = &f;
    double *pd = &d;
    long double *pld = &ld;

    /* Variables pour récupérer la représentation mémoire */
    unsigned int f_hex;
    unsigned long long d_hex;
    unsigned long long ld_hex;

    /* Lecture de la représentation binaire avec memcpy */
    memcpy(&f_hex, &f, sizeof(f));
    memcpy(&d_hex, &d, sizeof(d));

    /* Pour long double, on copie seulement 8 octets pour rester simple */
    memcpy(&ld_hex, &ld, sizeof(ld_hex));

    /* 3. Affichage AVANT la manipulation */
    printf("Avant la manipulation :\n");
    printf("Adresse de c   : %p, Valeur de c   : %x\n", (void *)pc, (unsigned char)*pc);
    printf("Adresse de s   : %p, Valeur de s   : %x\n", (void *)ps, (unsigned short)*ps);
    printf("Adresse de i   : %p, Valeur de i   : %x\n", (void *)pi, (unsigned int)*pi);
    printf("Adresse de li  : %p, Valeur de li  : %lx\n", (void *)pli, (unsigned long)*pli);
    printf("Adresse de lli : %p, Valeur de lli : %llx\n", (void *)plli, (unsigned long long)*plli);
    printf("Adresse de f   : %p, Valeur de f   : %x\n", (void *)pf, f_hex);
    printf("Adresse de d   : %p, Valeur de d   : %llx\n", (void *)pd, d_hex);
    printf("Adresse de ld  : %p, Valeur de ld  : %llx\n\n", (void *)pld, ld_hex);

    /* 4. Manipulation via pointeurs */
    *pc = 'B';
    *ps = 512;
    *pi = 0xA47865FE;
    *pli = 0x87654321;
    *plli = 0x9988776655443322LL;
    *pf = 1.0f;
    *pd = 1.0;
    *pld = 1.0L;

    /* Mise à jour des représentations mémoire */
    memcpy(&f_hex, &f, sizeof(f));
    memcpy(&d_hex, &d, sizeof(d));
    memcpy(&ld_hex, &ld, sizeof(ld_hex));

    /* 5. Affichage APRÈS la manipulation */
    printf("Apres la manipulation :\n");
    printf("Adresse de c   : %p, Valeur de c   : %x\n", (void *)pc, (unsigned char)*pc);
    printf("Adresse de s   : %p, Valeur de s   : %x\n", (void *)ps, (unsigned short)*ps);
    printf("Adresse de i   : %p, Valeur de i   : %x\n", (void *)pi, (unsigned int)*pi);
    printf("Adresse de li  : %p, Valeur de li  : %lx\n", (void *)pli, (unsigned long)*pli);
    printf("Adresse de lli : %p, Valeur de lli : %llx\n", (void *)plli, (unsigned long long)*plli);
    printf("Adresse de f   : %p, Valeur de f   : %x\n", (void *)pf, f_hex);
    printf("Adresse de d   : %p, Valeur de d   : %llx\n", (void *)pd, d_hex);
    printf("Adresse de ld  : %p, Valeur de ld  : %llx\n", (void *)pld, ld_hex);

    return 0;
}
