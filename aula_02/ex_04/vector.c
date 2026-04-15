#include <stdio.h>
#include <stdlib.h>
#include "vector.h"


Vector *vector_construct(){

    Vector *v = (Vector *)calloc(1, sizeof(Vector));
    v->size = 0;
    v->allocated = 10;
    v->data = (data_type *)calloc(v->allocated, sizeof(data_type));

    return v;
    
}

void vector_push_back(Vector *v, data_type val){
    if (v->size >= v->allocated){
        int new_allocated = 2 * v->allocated;

        data_type *new_data = (data_type *)realloc(v->data, new_allocated * sizeof(data_type));

        v->data = new_data;
        v->allocated = new_allocated;
    }
    v->data[v->size] = val;
    v->size++;
}

data_type vector_get(Vector *v, int i){
    if (i > v->size || i < 0){
        exit(EXIT_SUCCESS);
    } else {
        return v->data[i];
    }
}
void vector_set(Vector *v, int i, data_type val){
    if (i > v->size || i < 0){
        exit(EXIT_SUCCESS);
    } else {
        v->data[i] = val;
    }
}
int vector_size(Vector *v){
    return v->size;
}


void vector_destroy(Vector *v){
    if (!v){
        for (int i = 0; i < v->size; i++){
            free(v->data);
        }
        free(v);
    }
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
    for (int i = 0; i < v->data; i++){
        if (v->data[i] == val){
            return i;
        }
    }
    return -1;
}


void vector_destroy(Vector *v) {
    if (v == NULL) return;
    if (v->data != NULL) {
        free(v->data);
    }
    free(v);
}