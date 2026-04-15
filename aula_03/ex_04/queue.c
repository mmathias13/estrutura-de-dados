#include <stdlib.h>
#include "queue.h"

Queue *queue_construct() {
    Queue *q = (Queue *)calloc(1, sizeof(Queue));
    if (q != NULL) {
        q->v = vector_construct();
    }
    return q;
}

void queue_destroy(Queue *q) {
    if (q != NULL) {
        vector_destroy(q->v);
        free(q);
    }
}

int queue_size(Queue *q) {
    return vector_size(q->v);
}

void queue_enqueue(Queue *q, void *data) {
    vector_push_back(q->v, data);
}

void *queue_dequeue(Queue *q) {
    if (queue_size(q) == 0) {
        return NULL; 
    }
    return vector_pop_front(q->v);
}