#include <stdio.h>
#include <stdlib.h>

void troca_errado(int a, int b){
    int tmp = a;
    a = b;
    b = tmp;
}

void troca (int *a, int *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void min_max(const int *v, int n, int *min, int *max){
    *min = *max = v[0];
    for (int i = 1; i < n; i++){
        if (v[i] < *min){
            *min = v[i];
        }
        if (v[i] > *max){
            *max = v[i];
        }
    }
}

int main(int argc, char const *argv[])
{
    int x = 1, y = 2;
    troca_errado(x, y);
    printf("troca_errado: x = %d, y = %d\n", x, y);
    troca(&x, &y);
    printf("troca       : x = %d, y = %d\n", x, y);

    int v[5] = {7, -3, 12, 0, 5};
    int mn, mx;
    min_max(v, 5, &mn, &mx);
    printf("min = %d, max = %d\n", mn, mx);
    
    return 0;
}
