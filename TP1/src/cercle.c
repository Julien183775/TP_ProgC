#include <stdio.h>
#include <math.h> 

int main() {
    // Définition du rayon
    double rayon = 6.0; 

    // Calculs de l'aire et du périmètre
    double aire = M_PI * rayon * rayon;
    double perimetre = 2 * M_PI * rayon;

    // Affichage des résultats
    printf("Pour un cercle de rayon : %.2f\n", rayon);
    printf("L'aire du cercle est : %.2f\n", aire);
    printf("Le périmètre du cercle est : %.2f\n", perimetre);

    return 0;
}

