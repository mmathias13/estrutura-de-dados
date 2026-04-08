#include "product.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct product{

    char name[MAX_NAME_LENGTH];
    float price;
    float discount;
    int qtd;
    int sales;

};

Product *product_constructor(const char *name, float price, int qtd){
    Product *p = (Product *)malloc(sizeof(Product));
   
    if (price < 0 || qtd < 0){
        printf("VALOR INVALIDO\n");
        return NULL;
    } else {
        strncpy(p->name, name, 64);
        p->price = price;
        p->qtd = qtd;
        p->discount = 0;
        p->sales = 0;
        return p;
    }
}

const char *product_get_name(Product *product){
    return product->name;
}
float product_get_price(Product *product){
    return product->price;
}
float product_get_discount(Product *product){
    return product->discount;
}
int product_get_qtd(Product *product){
    return product->qtd;
}
int product_get_sales(Product *product){
    return product->sales;
}

void product_set_name(Product *product, const char *name){
    strncpy(product->name, name, 64);
}
void product_set_price(Product *product, float price){
    if (product->price < 0){
        printf("VALOR INVALIDO\n");
    } else {
        product->price = price;
    }
}
void product_set_discount(Product *product, float discount){
    if (product->discount <= 0){
        printf("VALOR INVALIDO\n");
    } else {
        product->discount = discount;
    }
}

void product_sell(Product *product, int quantity){
    if (quantity <= 0){
        printf("\n");
    } else if (quantity > product->qtd) {
        printf("ESTOQUE INSUFICIENTE\n");
    } else {
        product->qtd -= quantity;
        product->sales += quantity;
    }
}

void product_buy(Product *product, int quantity){
    if (quantity <= 0){
        printf("QUANTIDADE INVALIDA\n");
    } else {
        product->qtd += quantity;
    }
}

float product_get_price_with_discount(Product *product){
    return product->price * product->discount;
}

void product_print(Product *product){
    printf("Product(%s, %.2f, %.2f, %.2f, %d, %d)\n", 
            product->name, 
            product->price, 
            product->discount,
            product_get_price_with_discount(product), 
            product->qtd, 
            product->sales);
}


void product_destructor(Product *product){
    free(product);
}