#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char const *argv[])
{
    int n, sum = 0;
    float variance = 0;

    scanf("%d", &n);

    int *array = (int *)calloc(n, sizeof(int));

    for (int i = 0; i < n; i++){
        scanf("%d", &array[i]);
    }

    for (int i = 0; i < n; i++){
        sum += array[i];
    }

    float media = (float) sum / n;
    printf("%.2f\n", media);

    for (int i = 0; i < n; i++){
        variance += pow((array[i] - media), 2);
    }

    float standardDevitation = sqrt((variance) / (n - 1));
    printf("%.2f\n", standardDevitation);

    free(array);

    return 0;
}