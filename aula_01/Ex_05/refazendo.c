#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
    char nome[33];
    float *notas;
    float notaMedia;
}Filme;


int main(int argc, char const *argv[])
{
    int N, M;
    float somaMediasFilmes = 0, somaNotasFilme = 0;
    scanf("%d", &N);

    Filme *filmes = (Filme *)calloc(N, sizeof(Filme));
    for (int i = 0; i < N; i++){
        Filme *filme = (Filme *)calloc(1, sizeof(filme));
        scanf("%s\n", filmes[i].nome);
        scanf("%d", &M);
        for (int j = 0; j < M; j++){
            float *notas = (float *)calloc(M, sizeof(float));
            scanf("%f", &filmes[i].notas[j]);
        }
        for (int j = 0; j < M; j++){
            somaNotasFilme += filmes[i].notas[j];
        }
        float notaMedia = (float)somaNotasFilme / M;
        filmes[i].notaMedia = notaMedia;
    }

   //Cálculo da nota média dos filmes:
   for (int i = 0; i < N; i++){
    somaMediasFilmes += filmes[i].notaMedia;
   }

   float notaMediaFilmes = (float)somaMediasFilmes / N;

   //Imprime os filmes se forem maior que a média dos filmes
   for (int i = 0; i < N; i++){
    if (filmes[i].notaMedia > notaMediaFilmes){
        printf("%s\n", filmes[i].nome);
    }
   }

   //Bloco de liberação de memória
    for (int i = 0; i < N; i++){
        free(filmes[i].notas);
    }
    free(filmes);
    return 0;
}
