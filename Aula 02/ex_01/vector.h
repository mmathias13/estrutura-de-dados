
#ifndef _DATA_STRUCTURES_VECTOR_H_
#define _DATA_STRUCTURES_VECTOR_H_

typedef int data_type;

typedef struct
{
    data_type *data;
    int size;
    int allocated;
} Vector;

Vector *vector_construct();
void vector_destroy(Vector *v);

#endif