
#include <stdio.h>
#include <string.h>

#include "vector.h"

int main()
{
    Vector *v;

    v = vector_construct();
    vector_destroy(v);

    printf("OK!\n");

    return 0;
}