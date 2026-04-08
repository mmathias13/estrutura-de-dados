#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void processavetor(int vet[], int tam)
{
    int menor = 320000;
    int maior = -320000;
    for (int i = 0; i < tam; i++){
        if (vet[i] < menor){
            menor = vet[i];
        }
        if (vet[i] > maior){
            maior = vet[i];
        }
    }
    printf("%d\n", menor);
    printf("%d\n", maior);
}

int main(){

    int n = 0;
    scanf("%d", &n);
    int vet[n];
    
    for (int i = 0; i < n; i++){
        scanf("%d", &vet[i]);
    }

    processavetor(vet, n);

    return 0;
}