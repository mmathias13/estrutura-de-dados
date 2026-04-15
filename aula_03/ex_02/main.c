#include "product.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    char name[MAX_NAME_LENGTH], c;
    int n, qtd, sells;
    float price;

    scanf("%d", &n);
    Product **produtos = (Product**)malloc(n * sizeof(Product *));

    for (int i = 0; i < n; i++){
        scanf(" %[^\n]", name);
        scanf("%f %d %d", &price, &qtd, &sells);
        produtos[i] = product_constructor(name, price, qtd);
        product_sell(produtos[i], sells);
    }

    scanf(" %c", &c);

    if (c == 'N'){
        qsort(produtos, n, sizeof(Product *), product_compare_name);
    } else if (c == 'P'){
        qsort(produtos, n, sizeof(Product *), product_compare_price);
    } else if (c == 'S'){
        qsort(produtos, n, sizeof(Product *), product_compare_sales);
    }

    for (int i = 0; i < n; i++){
        product_print(produtos[i]);
    }

    for (int i = 0; i < n; i++){
        product_destructor(produtos[i]);
    }

    free(produtos);

    return 0;
}
