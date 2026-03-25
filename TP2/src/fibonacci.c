#include <stdio.h>

int main() {
    int n;
    int u0 = 0, u1 = 1, un;

    printf("Entrez la valeur de n : ");
    fflush(stdout);
    
    if (scanf("%d", &n) != 1) {
        return 1; 
    }

    for (int i = 0; i < n; i++) {
        if (i == 0) {
            printf("%d", u0);
        } else if (i == 1) {
            printf(", %d", u1);
        } else {
            un = u0 + u1;
            u0 = u1;
            u1 = un;
            printf(", %d", un);
        }
    }
    
    printf("\n");

    return 0;
}
