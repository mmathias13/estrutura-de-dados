#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "questao.h"
#include "lista.h"
 
#define TAM_MAX_LINHA 512
#define TAM_MAX_ID 32
#define TAM_MAX_NOME 128
 
static void ler_enunciado(FILE* fp, char* destino, size_t tamanho) {
    char linha[TAM_MAX_LINHA];
    char* inicio;
    size_t len;
 
    if (fgets(linha, sizeof(linha), fp) == NULL) {
        linha[0] = '\0';
    }
 
    inicio = linha;
    while (*inicio == ' ') inicio++;
 
    len = strlen(inicio);
    while (len > 0 && (inicio[len - 1] == '\n' || inicio[len - 1] == '\r')) {
        inicio[--len] = '\0';
    }
 
    strncpy(destino, inicio, tamanho - 1);
    destino[tamanho - 1] = '\0';
}
 
int main(int argc, char* argv[]) {
    FILE* fp;
    int n_banco, i;
    Lista* banco;
    Lista** provas = NULL;
    int num_provas = 0;
    Lista* merge_final = NULL;
    char nome_prova[TAM_MAX_NOME];
 
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <arquivo_entrada>\n", argv[0]);
        return EXIT_FAILURE;
    }
 
    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo: %s\n", argv[1]);
        return EXIT_FAILURE;
    }
 
    if (fscanf(fp, "%d", &n_banco) != 1) {
        fprintf(stderr, "Erro: formato invalido (numero de questoes)\n");
        fclose(fp);
        return EXIT_FAILURE;
    }
 
    banco = lista_criar();
    for (i = 0; i < n_banco; i++) {
        char id[TAM_MAX_ID];
        char enunciado[TAM_MAX_LINHA];
 
        if (fscanf(fp, "%31s", id) != 1) {
            fprintf(stderr, "Erro: formato invalido (id da questao)\n");
            break;
        }
        ler_enunciado(fp, enunciado, sizeof(enunciado));
 
        {
            Questao* q = questao_criar(id, enunciado);
            lista_inserir_inicio(banco, q);
        }
    }
 
    while (fscanf(fp, "%127s", nome_prova) == 1) {
        int n_prova, j;
        Lista* prova = lista_criar();
 
        if (fscanf(fp, "%d", &n_prova) != 1) {
            fprintf(stderr, "Erro: formato invalido (numero de questoes da prova)\n");
            lista_destruir_nos(prova);
            break;
        }
 
        for (j = 0; j < n_prova; j++) {
            char id[TAM_MAX_ID];
            Questao* q;
 
            if (fscanf(fp, "%31s", id) != 1) {
                fprintf(stderr, "Erro: formato invalido (id na prova)\n");
                break;
            }
            q = lista_buscar(banco, id);
            if (q != NULL) {
                lista_inserir_inicio(prova, q);
            } else {
                fprintf(stderr, "Aviso: id %s nao encontrado no banco\n", id);
            }
        }
 
        lista_imprimir(prova, nome_prova);
 
        provas = (Lista**) realloc(provas, (num_provas + 1) * sizeof(Lista*));
        if (provas == NULL) {
            fprintf(stderr, "Erro: falha ao realocar vetor de provas\n");
            fclose(fp);
            return EXIT_FAILURE;
        }
        provas[num_provas] = prova;
        num_provas++;
    }
 
    fclose(fp);
 
    if (num_provas >= 1) {
        merge_final = provas[0];
        for (i = 1; i < num_provas; i++) {
            Lista* novo_merge = lista_merge(merge_final, provas[i]);
            if (i > 1) {
                lista_destruir_nos(merge_final);
            }
            merge_final = novo_merge;
        }
 
        lista_imprimir(merge_final, "Merge");
        lista_remover_duplicadas(merge_final);
        lista_imprimir(merge_final, "Merge");
    }
 
    for (i = 0; i < num_provas; i++) {
        if (num_provas == 1 && provas[i] == merge_final) continue;
        lista_destruir_nos(provas[i]);
    }
    if (merge_final != NULL) {
        lista_destruir_nos(merge_final);
    }
    free(provas);
 
    lista_destruir_completa(banco);
 
    return EXIT_SUCCESS;
}