
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
        printf("%d\n", v->data[i]);

    vector_destroy(v);

    return 0;
}