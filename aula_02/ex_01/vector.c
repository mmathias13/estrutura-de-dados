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
void vector_destroy(Vector *v){
    if (v != NULL){
        if (v->data != NULL){
            free(v->data);
        }
        free(v);
    }
}