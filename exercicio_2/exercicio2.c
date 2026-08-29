#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
typedef struct {
    char *nome;
    float valor;
} TipoProduto;
 
typedef struct {
    int quantidade;
    TipoProduto *produto;
} ItemEstoque;
 
typedef struct {
    float valor;
    int quantidadeItens;
    ItemEstoque *itens;
} Estoque;
 
typedef struct {
    char *nome;
    Estoque *estoque;
} Filial;
 
typedef struct {
    char *nome;
    float valorTotal;
    int quantidadeFiliais;
    Filial *filiais;
} Supermercado;
 
void calculaEstoqueFilial(Filial *filial)
{
    int i;
    float soma;
 
    soma = 0;
    for (i = 0; i < filial->estoque->quantidadeItens; i++) {
        soma = soma + filial->estoque->itens[i].quantidade * filial->estoque->itens[i].produto->valor;
    }
 
    filial->estoque->valor = soma;
}
 
void calculaEstoqueSupermercado(Supermercado *mercado)
{
    int i;
    float soma;
 
    soma = 0;
    for (i = 0; i < mercado->quantidadeFiliais; i++) {
        soma = soma + mercado->filiais[i].estoque->valor;
    }
 
    mercado->valorTotal = soma;
}
 
void imprimeSupermercado(Supermercado *mercado)
{
    int i;
    int j;
 
    printf("Nome do Supermercado: %s\n", mercado->nome);
    for (i = 0; i < mercado->quantidadeFiliais; i++) {
        printf("Filial: %s\n", mercado->filiais[i].nome);
        printf("Estoque: %.2f\n", mercado->filiais[i].estoque->valor);
        for (j = 0; j < mercado->filiais[i].estoque->quantidadeItens; j++) {
            printf("Item: %s, valor unitário: %.2f, quantidade: %d\n",
                   mercado->filiais[i].estoque->itens[j].produto->nome,
                   mercado->filiais[i].estoque->itens[j].produto->valor,
                   mercado->filiais[i].estoque->itens[j].quantidade);
        }
    }
}
 
int main()
{
    FILE *arquivo;
    TipoProduto *produtos;
    Supermercado *mercado;
    char aux[100];
    int quantidadeProdutos;
    int quantidadeFiliais;
    int quantidadeItens;
    int codigo;
    int quantidade;
    int i;
    int j;
 
    arquivo = fopen("entrada.txt", "r");
 
    fscanf(arquivo, "%d", &quantidadeProdutos);
    produtos = (TipoProduto *) malloc(quantidadeProdutos * sizeof(TipoProduto));
 
    for (i = 0; i < quantidadeProdutos; i++) {
        fscanf(arquivo, "%d", &codigo);
        fscanf(arquivo, "%s", aux);
        produtos[i].nome = (char *) malloc((strlen(aux) + 1) * sizeof(char));
        strcpy(produtos[i].nome, aux);
        fscanf(arquivo, "%f", &produtos[i].valor);
    }
 
    mercado = (Supermercado *) malloc(sizeof(Supermercado));
 
    fscanf(arquivo, "%s", aux);
    mercado->nome = (char *) malloc((strlen(aux) + 1) * sizeof(char));
    strcpy(mercado->nome, aux);
 
    fscanf(arquivo, "%d", &quantidadeFiliais);
    mercado->quantidadeFiliais = quantidadeFiliais;
    mercado->valorTotal = 0;
    mercado->filiais = (Filial *) malloc(quantidadeFiliais * sizeof(Filial));
 
    for (i = 0; i < quantidadeFiliais; i++) {
        fscanf(arquivo, "%s", aux);
        mercado->filiais[i].nome = (char *) malloc((strlen(aux) + 1) * sizeof(char));
        strcpy(mercado->filiais[i].nome, aux);
 
        fscanf(arquivo, "%d", &quantidadeItens);
 
        mercado->filiais[i].estoque = (Estoque *) malloc(sizeof(Estoque));
        mercado->filiais[i].estoque->valor = 0;
        mercado->filiais[i].estoque->quantidadeItens = quantidadeItens;
        mercado->filiais[i].estoque->itens = (ItemEstoque *) malloc(quantidadeItens * sizeof(ItemEstoque));
 
        for (j = 0; j < quantidadeItens; j++) {
            fscanf(arquivo, "%d", &codigo);
            fscanf(arquivo, "%d", &quantidade);
            mercado->filiais[i].estoque->itens[j].quantidade = quantidade;
            mercado->filiais[i].estoque->itens[j].produto = &produtos[codigo - 1];
        }
 
        calculaEstoqueFilial(&mercado->filiais[i]);
    }
 
    fclose(arquivo);
 
    calculaEstoqueSupermercado(mercado);
 
    imprimeSupermercado(mercado);
 
    for (i = 0; i < mercado->quantidadeFiliais; i++) {
        free(mercado->filiais[i].estoque->itens);
        free(mercado->filiais[i].estoque);
        free(mercado->filiais[i].nome);
    }
    free(mercado->filiais);
    free(mercado->nome);
    free(mercado);
 
    for (i = 0; i < quantidadeProdutos; i++) {
        free(produtos[i].nome);
    }
    free(produtos);
 
    return 0;
}
 