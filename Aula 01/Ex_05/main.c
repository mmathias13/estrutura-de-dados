#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char nome[32];
    float *notas;
    int qtd_notas;
    float media;
} Filme;

int main() {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    Filme *filmes = (Filme *)malloc(N * sizeof(Filme));
    float soma_medias = 0;

    for (int i = 0; i < N; i++) {
        scanf("%s", filmes[i].nome);
        scanf("%d", &filmes[i].qtd_notas);

        filmes[i].notas = (float *)malloc(filmes[i].qtd_notas * sizeof(float));
        float soma_filme = 0;

        for (int j = 0; j < filmes[i].qtd_notas; j++) {
            scanf("%f", &filmes[i].notas[j]);
            soma_filme += filmes[i].notas[j];
        }

        if (filmes[i].qtd_notas > 0)
            filmes[i].media = soma_filme / filmes[i].qtd_notas;
        else
            filmes[i].media = 0;

        soma_medias += filmes[i].media;
    }

    float media_global = 0;
    if (N > 0)
        media_global = soma_medias / N;

    for (int i = 0; i < N; i++) {
        if (filmes[i].media > media_global)
            printf("%s\n", filmes[i].nome);
    }

    for (int i = 0; i < N; i++)
        free(filmes[i].notas);

    free(filmes);

    return 0;
}