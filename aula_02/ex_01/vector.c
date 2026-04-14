#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Vector *vector_construct(){

    Vector *v = (Vector *)calloc(1, sizeof(Vector));
    v->size = 0;
    v->allocated = 10;
    v->data = (data_type *)calloc(v->allocated, sizeof(data_type));

    return v;
    
}


void vector_destroy(Vector *v){
    if (!v){
        for (int i = 0; i < v->size; i++){
            free(v->data);
        }
        free(v);
    }
}