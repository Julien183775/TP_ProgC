#include <stdio.h>

int main() {
    unsigned int d = 268439552; 

    int bit_4 = (d >> 28) & 1;  
    int bit_20 = (d >> 12) & 1; 

    if (bit_4 == 1 && bit_20 == 1) {
        printf("1\n");
    } else {
        printf("0\n");
    }

    return 0;
}
