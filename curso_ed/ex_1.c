#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int x = 10;
    int *p = &x;

    printf("x      = %d\n", x);
    printf("&x     = %p\n", (void *) &x);
    printf("p      = %p\n", (void*)p);
    printf("*p     = %d\n", *p);
    printf("&p     = %p\n", (void*)&p);

    *p = 20;
    printf("Depois de *p = 20: x = %d\n", x);

    int y = 99;
    p = &y;
    printf("p = &y: x = %d, y = %d, *p = %d\n", x, y, *p);

    return 0;
}
/* code */