#include <stdlib.h>
#include "stack.h"

Stack *stack_construct() {
    Stack *s = (Stack *)malloc(sizeof(Stack));
    if (s != NULL) {
        s->v = vector_construct();
    }
    return s;
}

void stack_destroy(Stack *s) {
    if (s != NULL) {
        vector_destroy(s->v);
        free(s);
    }
}

int stack_size(Stack *s) {
    return vector_size(s->v);
}

void stack_push(Stack *s, void *data) {
    vector_push_back(s->v, data);
}

void *stack_pop(Stack *s) {
    if (stack_size(s) == 0) return NULL;
    return vector_pop_back(s->v);
}