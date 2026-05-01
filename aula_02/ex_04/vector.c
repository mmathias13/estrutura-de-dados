#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Vector *vector_construct(){
    Vector *vector = (Vector*)calloc(1, sizeof(Vector));
    vector->size = 0;
    vector->allocated = 10;
    vector->data = (data_type*)calloc(vector->allocated, sizeof(data_type));

    return vector;
}

void vector_push_back(Vector *v, data_type val){
    if (v->size >= v->allocated){
        v->allocated *= 2;
        v->data = (data_type *)realloc(v->data, v->allocated * sizeof(data_type));
    }
    v->data[v->size] = val;
    v->size++;
}

data_type vector_get(Vector *v, int i){
    if (i < 0 || i >= v->size){
        exit(EXIT_FAILURE); 
    } else {
        return v->data[i];
    }
}
void vector_set(Vector *v, int i, data_type val){
    if (i < 0 || i >= v->size){
        exit(EXIT_FAILURE);
    } else {
        v->data[i] = val;
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

void vector_destroy(Vector *v){
    if (v != NULL){
        if (v->data != NULL){
            free(v->data);
        }
        free(v);
    }
}

