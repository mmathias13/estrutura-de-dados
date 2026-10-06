#ifndef LISTA_H
#define LISTA_H
 
#include "questao.h"
 
typedef struct lista Lista;
 
Lista* lista_criar(void);
void lista_inserir_inicio(Lista* lista, Questao* q);
Questao* lista_buscar(const Lista* lista, const char* id);
void lista_imprimir(const Lista* lista, const char* nome_prova);
Lista* lista_merge(const Lista* l1, const Lista* l2);
void lista_remover_duplicadas(Lista* lista);
void lista_destruir_nos(Lista* lista);
void lista_destruir_completa(Lista* lista);
 
#endif
 