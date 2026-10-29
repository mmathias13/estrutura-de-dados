#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int n = 5;

    int *a = malloc(n * sizeof(int));
    if (a == NULL){
        printf("Erro de memória\n");
        return 1;
    }
    for (int i = 0; i < n; i++){
        a[i] = i * i;
    }

    int *b = calloc(n, sizeof(int));
    if (b == NULL){
        free(a);
        return 1;
    }

    printf("a (malloc + preenchido): ");
    for (int i = 0; i < n; i++){
        printf("%d ", a[i]);
    }
    printf("\nb (calloc, zerado):          ");
    for (int i = 0; i < n; i++){
        printf("%d ", b[i]);
    }
    printf("\n");

    free(a);
    free(b);

    return 0;
}
