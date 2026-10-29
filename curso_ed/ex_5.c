#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int capacidade = 2, tamanho = 0;
    int *v = malloc(tamanho * sizeof(*v));
    if (v == NULL){
        return 1;
    }

    for (int x = 10; x <= 50; x += 10){
        if (tamanho == capacidade){
            int nova_cap = capacidade * 2;
            int *tmp = realloc(v, nova_cap * sizeof(*v));
            if (tmp == NULL){
                free(v);
                return 1;
            }
            v = tmp;
            capacidade = nova_cap;
            printf("Cresceu para %d posicoes\n", capacidade);
        }
        v[tamanho++] = x;
    }
    printf("v = ");
    for (int i = 0; i < tamanho; i++){
       printf("%d ", v[i]);
    }
    printf("(tamanho %d, capacidade %d)\n", tamanho, capacidade);

    free(v);
    return 0;
}
