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
        exit(EXIT_SUCCESS);
    }
}

void vector_set(Vector *v, int i, data_type val){
    if (i >= 0 && i < v->size){
        v->data[i] = val;
    } else {
        exit(EXIT_SUCCESS);
    }
}

int vector_size(Vector *v){
    return v->size;
}

int vector_find(Vector *v, data_type val, VectorCmpFn cmp_fn){
    for (int i = 0; i < v->size; i++){
        if (cmp_fn(v->data[i], val) == 0){
            return i;
        }
    }
    return -1;
}

data_type vector_max(Vector *v, VectorCmpFn cmp_fn){
    if (v->size == 0) return NULL;
    data_type maiorElemento = v->data[0];

    for (int i = 1; i < v->size; i++){
        if (cmp_fn(v->data[i], maiorElemento) > 0){
            maiorElemento = v->data[i];
        }
    }
    return maiorElemento;
}

data_type vector_min(Vector *v, VectorCmpFn cmp_fn){
    if (v->size == 0) return NULL;
    data_type menorElemento = v->data[0];

    for (int i = 1; i < v->size; i++){
        if (cmp_fn(v->data[i], menorElemento) < 0){
            menorElemento = v->data[i];
        }
    }
    return menorElemento;
}

int vector_argmax(Vector *v, VectorCmpFn cmp_fn){
    data_type maiorElemento = vector_max(v, cmp_fn);
    return vector_find(v, maiorElemento, cmp_fn);
}

int vector_argmin(Vector *v, VectorCmpFn cmp_fn){
    data_type menorElemento = vector_min(v, cmp_fn);
    return vector_find(v, menorElemento, cmp_fn);
}

data_type vector_remove(Vector *v, int i){
    data_type item_removido = v->data[i];

    for(int j = i; j < v->size - 1; j++){
        v->data[j] = v->data[j + 1];
    }
    v->size--;
    return item_removido;
}

data_type vector_pop_front(Vector *v){
    return vector_remove(v, 0);
}

data_type vector_pop_back(Vector *v){
    return vector_remove(v, v->size - 1); 
}

void vector_insert(Vector *v, int i, data_type val){
    if (v->allocated == v->size){
        v->allocated *= 2; 
        v->data = (data_type *) realloc(v->data, v->allocated * sizeof(data_type));
    }
    for (int j = v->size; j > i; j--){
        v->data[j] = v->data[j - 1];
    }
    v->data[i] = val;
    v->size++;
}

void vector_swap(Vector *v, int i, int j){
    data_type aux;
    aux = v->data[i];
    v->data[i] = v->data[j];
    v->data[j] = aux;
}

void vector_sort(Vector *v, VectorCmpFn cmp_fn) {
    int trocou;
    for (int i = 0; i < v->size - 1; i++) {
        trocou = 0;
        for (int j = 0; j < v->size - i - 1; j++) {
            if (cmp_fn(v->data[j], v->data[j + 1]) > 0) {
                vector_swap(v, j, j + 1);
                trocou = 1;
            }
        }
        if (!trocou) {
            break;
        }
    }
}

int vector_binary_search(Vector *v, data_type val, VectorCmpFn cmp_fn) {
    int baixo = 0;
    int alto = v->size - 1;

    while (baixo <= alto) {
        int meio = baixo + (alto - baixo) / 2;
        int cmp_result = cmp_fn(v->data[meio], val);

        if (cmp_result == 0) {
            return meio;
        } else if (cmp_result < 0) {
            baixo = meio + 1;
        } else {
            alto = meio - 1;
        }
    }
    return -1;
}

void vector_reverse(Vector *v){
    for (int i = 0; i < v->size / 2; i++){
        vector_swap(v, i, v->size - 1 - i);
    }
}

void vector_destroy(Vector *v) {
    if (v == NULL) return;
    if (v->data != NULL) {
        free(v->data);
    }
    free(v);
}