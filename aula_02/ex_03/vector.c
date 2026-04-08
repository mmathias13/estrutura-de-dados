
#include <stdio.h>
#include <string.h>

#include "vector.h"

int main()
{
    int n, value;
    Vector *v;

    v = vector_construct();

    scanf("%d", &n);

    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &value);
        vector_push_back(v, value);
    }

    for (int i = 0; i < v->size; i++)
        vector_set(v, i, vector_get(v, i) * 2);

    for (int i = 0; i < vector_size(v); i++)
        printf("%d\n", vector_get(v, i));

    vector_destroy(v);

    return 0;
}