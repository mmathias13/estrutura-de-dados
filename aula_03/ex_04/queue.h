#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "vector.h"

typedef struct {
    Vector *v;
} Queue;

Queue *queue_construct();
void queue_destroy(Queue *q);
int queue_size(Queue *q);
void queue_enqueue(Queue *q, void *data);
void *queue_dequeue(Queue *q);

#endif