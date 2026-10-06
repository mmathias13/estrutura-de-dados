#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
 
typedef struct nodo {
    Questao* q;
    struct nodo* prox;
} Nodo;
 
struct lista {
    Nodo* inicio;
};
 
static Nodo* nodo_criar(Questao* q) {
    Nodo* n = (Nodo*) malloc(sizeof(Nodo));
    if (n == NULL) {
        fprintf(stderr, "Erro: falha ao alocar memoria para Nodo\n");
        exit(EXIT_FAILURE);
    }
    n->q = q;
    n->prox = NULL;
    return n;
}
 
Lista* lista_criar(void) {
    Lista* lista = (Lista*) malloc(sizeof(Lista));
    if (lista == NULL) {
        fprintf(stderr, "Erro: falha ao alocar memoria para Lista\n");
        exit(EXIT_FAILURE);
    }
    lista->inicio = NULL;
    return lista;
}
 
void lista_inserir_inicio(Lista* lista, Questao* q) {
    Nodo* n = nodo_criar(q);
    n->prox = lista->inicio;
    lista->inicio = n;
}
 
Questao* lista_buscar(const Lista* lista, const char* id) {
    Nodo* atual = lista->inicio;
    while (atual != NULL) {
        if (strcmp(questao_get_id(atual->q), id) == 0) {
            return atual->q;
        }
        atual = atual->prox;
    }
    return NULL;
}
 
void lista_imprimir(const Lista* lista, const char* nome_prova) {
    Nodo* atual = lista->inicio;
    printf("Prova: %s\n", nome_prova);
    while (atual != NULL) {
        printf("ID: %s, Enunciado: %s\n",
               questao_get_id(atual->q),
               questao_get_enunciado(atual->q));
        atual = atual->prox;
    }
}
 
Lista* lista_merge(const Lista* l1, const Lista* l2) {
    Lista* resultado = lista_criar();
    Nodo* atual;
    Nodo* cauda = NULL;
 
    atual = l1->inicio;
    while (atual != NULL) {
        Nodo* novo = nodo_criar(atual->q);
        if (cauda == NULL) {
            resultado->inicio = novo;
        } else {
            cauda->prox = novo;
        }
        cauda = novo;
        atual = atual->prox;
    }
 
    atual = l2->inicio;
    while (atual != NULL) {
        Nodo* novo = nodo_criar(atual->q);
        if (cauda == NULL) {
            resultado->inicio = novo;
        } else {
            cauda->prox = novo;
        }
        cauda = novo;
        atual = atual->prox;
    }
 
    return resultado;
}
 
void lista_remover_duplicadas(Lista* lista) {
    Nodo* atual = lista->inicio;
    while (atual != NULL) {
        Nodo* comparador = atual;
        while (comparador->prox != NULL) {
            if (strcmp(questao_get_id(atual->q),
                       questao_get_id(comparador->prox->q)) == 0) {
                Nodo* duplicado = comparador->prox;
                comparador->prox = duplicado->prox;
                free(duplicado);
            } else {
                comparador = comparador->prox;
            }
        }
        atual = atual->prox;
    }
}
 
void lista_destruir_nos(Lista* lista) {
    Nodo* atual = lista->inicio;
    while (atual != NULL) {
        Nodo* proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    free(lista);
}
 
void lista_destruir_completa(Lista* lista) {
    Nodo* atual = lista->inicio;
    while (atual != NULL) {
        Nodo* proximo = atual->prox;
        questao_destruir(atual->q);
        free(atual);
        atual = proximo;
    }
    free(lista);
}