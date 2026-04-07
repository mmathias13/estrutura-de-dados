#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

Vector* vector_construct() {
    Vector *v = (Vector*) calloc(1, sizeof(Vector));
    if (v == NULL) return NULL;

    v->allocated = 10; 
    v->size = 0;      
    v->data = (data_type*) calloc(v->allocated, sizeof(data_type));

    if (v->data == NULL) {
        free(v);
        return NULL;
    }
    return v;
}

void vector_push_back(Vector *v, data_type val) {
    if (v->size == v->allocated) {
        int new_allocated = v->allocated * 2;
        data_type *temp = (data_type*) realloc(v->data, new_allocated * sizeof(data_type));
        
        if (temp == NULL) return; 

        v->data = temp;
        v->allocated = new_allocated;
    }
    v->data[v->size] = val;
    v->size++;
}

data_type vector_get(Vector *v, int i){
    if (i >= 0 && i < v->size){
        return v->data[i];
    } else {
        //printf("Erro: Nao ha valor definido para o vetor na posicao %d.\n", i);
        exit(EXIT_SUCCESS);
    }
}
void vector_set(Vector *v, int i, data_type val){
    if (i >= 0 && i < v->size){
        v->data[i] = val;
    } else {
        //printf("Erro: Nao ha valor definido para o vetor na posicao %d.\n", i);
        exit(EXIT_SUCCESS);
    }
}
int vector_size(Vector *v){
    return v->size;
}

int vector_find(Vector *v, data_type val){
    for (int i = 0; i < v->size; i++){
        if (v->data[i] == val){
            return i;
        }
    }
    return -1;
}

// Retorna o maior elemento do vector (assumindo que podemos comparar elementos usando o operador "<")
data_type vector_max(Vector *v){
    int maiorElemento = 0;

    for (int i = 0; i < v->size; i++){
        if (i == 0){
            maiorElemento = v->data[i];
        }
        if (v->data[i] > maiorElemento){
            maiorElemento = v->data[i];
        }
    }
    return maiorElemento;
}

// Retorna o menor elemento do vector (assumindo que podemos comparar elementos usando o operador "<")
data_type vector_min(Vector *v){
        int menorElemento = 0;

    for (int i = 0; i < v->size; i++){
        if (i == 0){
            menorElemento = v->data[i];
        }
        if (v->data[i] < menorElemento){
            menorElemento = v->data[i];
        }
    }
    return menorElemento;
}

// Retorna o Ã­ndice do maior elemento do vector (assumindo que podemos comparar elementos usando o operador "<")
int vector_argmax(Vector *v){
    int maiorElemento = vector_max(v);

    return vector_find(v, maiorElemento);
}

// Retorna o Ã­ndice do menor elemento do vector (assumindo que podemos comparar elementos usando o operador "<")
int vector_argmin(Vector *v){
    int menorElemento = vector_min(v);

    return vector_find(v, menorElemento);
}

void vector_destroy(Vector *v) {
    if (v == NULL) return;
    if (v->data != NULL) {
        free(v->data);
    }
    free(v);
}