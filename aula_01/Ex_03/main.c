#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){

    int n = 0;
    scanf("%d", &n);

    int *v = (int * )malloc(n * sizeof(int));

    for(int i = 0; i < n; i++){
        scanf("%d", &v[i]);
    }

    int soma = 0;

    for (int i = 0; i < n; i++){
        soma += v[i];
    }

    float media = (float)soma / n;
    printf("%.2f\n", media);

    float variancia = 0;

    for (int i = 0; i < n; i++){
        variancia += ((v[i] - media) * (v[i] - media));     
    }

    float dp = sqrt((variancia / (n - 1)));

    printf("%.2f\n", dp);

    free(v);

    return 0;
}