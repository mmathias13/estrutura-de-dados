#include <stdio.h>
#include <stdlib.h>

void biggestNumber(int array[], int n, int *maior){
    for (int i = 0; i < n; i++){
        if (array[i] > *maior){
            *maior = array[i];
        }
    }
}
void lowestNumber(int array[], int n, int *menor){
    for (int i = 0; i < n; i++){
        if (array[i] < *menor){
            *menor = array[i];
        }
    }
}

int main(int argc, char const *argv[])
{
    int n, maior = -3200000, menor = 3200000;
    scanf("%d", &n);

    int *array = (int *)calloc(n, sizeof(int));

    for (int i = 0; i < n; i++){
        scanf("%d", &array[i]);
    }

    biggestNumber(array, n, &maior);
    lowestNumber(array, n, &menor);

    printf("%d\n%d", menor, maior);

    free(array);

    return 0;
}
