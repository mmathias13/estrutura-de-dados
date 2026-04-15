#ifndef _DATA_STRUCTURES_VECTOR_H_
#define _DATA_STRUCTURES_VECTOR_H_

typedef void *data_type;

typedef int (*VectorCmpFn)(const void *, const void *);

typedef struct
{
    data_type *data;
    int size;
    int allocated;
} Vector;

Vector *vector_construct();
void vector_push_back(Vector *v, data_type val);
data_type vector_get(Vector *v, int i);
void vector_set(Vector *v, int i, data_type val);
int vector_size(Vector *v);

int vector_find(Vector *v, data_type val, VectorCmpFn cmp_fn);
data_type vector_max(Vector *v, VectorCmpFn cmp_fn);
data_type vector_min(Vector *v, VectorCmpFn cmp_fn);
int vector_argmax(Vector *v, VectorCmpFn cmp_fn);
int vector_argmin(Vector *v, VectorCmpFn cmp_fn);

data_type vector_remove(Vector *v, int i);
data_type vector_pop_front(Vector *v);
data_type vector_pop_back(Vector *v);
void vector_insert(Vector *v, int i, data_type val);
void vector_swap(Vector *v, int i, int j);

void vector_sort(Vector *v, VectorCmpFn cmp_fn);
int vector_binary_search(Vector *v, data_type val, VectorCmpFn cmp_fn);

void vector_reverse(Vector *v);
Vector *vector_copy(Vector *v);
void vector_clear(Vector *v);
void vector_destroy(Vector *v);

#endif