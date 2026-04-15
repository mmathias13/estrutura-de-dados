#include "product.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    char name[MAX_NAME_LENGTH], c;
    float price;
    int qtd, n;

    scanf("%s %f %d", name, &price, &qtd);

    Product *product = product_constructor(name, price, qtd);

    scanf("%d", &n);

    for (int i = 0; i < n; i++){
        scanf("% c", &c);

        if (c == 'P'){
            product_print(product);
        } else if (c == 'S'){
            int qtdVendida;
            scanf("%d", &qtdVendida);
            product_sell(product, qtdVendida);
        } else if (c == 'B'){
            int qtdComprada;
            scanf("%d", &qtdComprada);
            product_buy(product, qtdComprada);
        } else if (c == 'D'){
            float new_discount;
            scanf("%f", &new_discount);
            product_set_discount(product, new_discount);
        } else if (c == 'Q'){
            float new_price;
            scanf("%f", &new_price);
            product_set_price(product, new_price);
        } else if (c == 'N'){
            char new_name[MAX_NAME_LENGTH];
            scanf("%*c");
            scanf("%s", new_name);
            product_set_name(product, new_name);
            
        }
    }

    return 0;
}
