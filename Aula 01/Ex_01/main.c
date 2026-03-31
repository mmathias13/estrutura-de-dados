#include <stdio.h>

int main(){

    int num = 0;
    scanf("%d", &num);
    char *c = (char *) &num;

    for (int i = 0; i < 4; i++){
        printf("%d\n", c[i]);
    }

    return 0;
}