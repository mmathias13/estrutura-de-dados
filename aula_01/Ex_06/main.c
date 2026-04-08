#include <stdio.h>
#include <stdlib.h>

int main() {
    int tamRoleta, nGiros;

    scanf("%d %d", &tamRoleta, &nGiros);

    int pos = 0;
    int giroAtual;

    for (int i = 0; i < nGiros; i++) {
        scanf("%d", &giroAtual);

        pos = (pos + giroAtual) % tamRoleta;
        
        if (pos < 0) {
            pos += tamRoleta;
        }
    }

    printf("%d\n", pos);

    return 0;
}