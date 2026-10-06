#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "questao.h"
 
struct questao {
    char* id;
    char* enunciado;
};
 
static char* duplicar_string(const char* origem) {
    size_t tamanho = strlen(origem) + 1;
    char* copia = (char*) malloc(tamanho);
    if (copia == NULL) {
        fprintf(stderr, "Erro: falha ao alocar memoria para string\n");
        exit(EXIT_FAILURE);
    }
    memcpy(copia, origem, tamanho);
    return copia;
}
 
Questao* questao_criar(const char* id, const char* enunciado) {
    Questao* q = (Questao*) malloc(sizeof(Questao));
    if (q == NULL) {
        fprintf(stderr, "Erro: falha ao alocar memoria para Questao\n");
        exit(EXIT_FAILURE);
    }
    q->id = duplicar_string(id);
    q->enunciado = duplicar_string(enunciado);
    return q;
}
 
void questao_destruir(Questao* q) {
    if (q == NULL) return;
    free(q->id);
    free(q->enunciado);
    free(q);
}
 
const char* questao_get_id(const Questao* q) {
    return q->id;
}
 
const char* questao_get_enunciado(const Questao* q) {
    return q->enunciado;
}