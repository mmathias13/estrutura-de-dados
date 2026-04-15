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
    if (price < 0 || qtd < 0){
        printf("VALOR INVALIDO\n");
        return NULL;
    } 
    
    Product *p = (Product *)malloc(sizeof(Product));
    
    strncpy(p->name, name, MAX_NAME_LENGTH);
    p->name[MAX_NAME_LENGTH - 1] = '\0';
    p->price = price;
    p->qtd = qtd;
    p->discount = 0;
    p->sales = 0;
    return p;
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
    strncpy(product->name, name, MAX_NAME_LENGTH);
    product->name[MAX_NAME_LENGTH - 1] = '\0';
}
void product_set_price(Product *product, float price){
    if (price < 0){
        printf("VALOR INVALIDO\n");
    } else {
        product->price = price;
    }
}
void product_set_discount(Product *product, float discount){
    if (discount < 0){
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
    return product->price * ( 1.0 - product->discount);
}

void product_print(void *p){
    // Fazemos a conversão do ponteiro genérico para Product* aqui dentro!
    Product *product = (Product *)p; 
    
    printf("Product(%s, %.2f, %.2f, %.2f, %d, %d)\n", 
            product->name, 
            product->price, 
            product->discount,
            product_get_price_with_discount(product), 
            product->qtd, 
            product->sales);
}

// CORREÇÃO: Usando a forma pedida pelo professor (cast simples)
int product_compare_name(const void *v1, const void *v2) {
    Product *p1 = (Product *)v1;
    Product *p2 = (Product *)v2;
    
    return strcmp(product_get_name(p1), product_get_name(p2));
}

int product_compare_price(const void *v1, const void *v2) {
    Product *p1 = (Product *)v1;
    Product *p2 = (Product *)v2;
    
    float price1 = product_get_price(p1);
    float price2 = product_get_price(p2);
    
    if (price1 < price2) return -1;
    if (price1 > price2) return 1;
    return 0;
}

int product_compare_sales(const void *v1, const void *v2) {
    Product *p1 = (Product *)v1;
    Product *p2 = (Product *)v2;
    
    int sales1 = product_get_sales(p1);
    int sales2 = product_get_sales(p2);
    
    return sales1 - sales2; 
}

void product_destructor(void *p){
    Product *product = (Product *)p;
    free(product);
}