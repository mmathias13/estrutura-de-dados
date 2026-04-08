#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

Vector* vector_construct() {
    Vector *v = (Vector*) calloc(1, sizeof(Vector));
    if (v == NULL) return NULL;

    v->allocated = 10; 
    v->size = 0;      
    v->data = (data_type*) calloc(v->allocated, sizeof(data_type));

    if (v->data == NULL) {
        free(v);
        return NULL;
    }
    return v;
}

void vector_push_back(Vector *v, data_type val) {
    if (v->size == v->allocated) {
        int new_allocated = v->allocated * 2;
        data_type *temp = (data_type*) realloc(v->data, new_allocated * sizeof(data_type));
        
        if (temp == NULL) return; 

        v->data = temp;
        v->allocated = new_allocated;
    }
    v->data[v->size] = val;
    v->size++;
}

data_type vector_get(Vector *v, int i){
    if (i >= 0 && i < v->size){
        return v->data[i];
    } else {
        //printf("Erro: Nao ha valor definido para o vetor na posicao %d.\n", i);
        exit(EXIT_SUCCESS);
    }
}
void vector_set(Vector *v, int i, data_type val){
    if (i >= 0 && i < v->size){
        v->data[i] = val;
    } else {
        //printf("Erro: Nao ha valor definido para o vetor na posicao %d.\n", i);
        exit(EXIT_SUCCESS);
    }
}
int vector_size(Vector *v){
    return v->size;
}

int vector_find(Vector *v, data_type val){
    for (int i = 0; i < v->size; i++){
        if (v->data[i] == val){
            return i;
        }
    }
    return -1;
}

// Retorna o maior elemento do vector (assumindo que podemos comparar elementos usando o operador "<")
data_type vector_max(Vector *v){
    int maiorElemento = 0;

    for (int i = 0; i < v->size; i++){
        if (i == 0){
            maiorElemento = v->data[i];
        }
        if (v->data[i] > maiorElemento){
            maiorElemento = v->data[i];
        }
    }
    return maiorElemento;
}

// Retorna o menor elemento do vector (assumindo que podemos comparar elementos usando o operador "<")
data_type vector_min(Vector *v){
        int menorElemento = 0;

    for (int i = 0; i < v->size; i++){
        if (i == 0){
            menorElemento = v->data[i];
        }
        if (v->data[i] < menorElemento){
            menorElemento = v->data[i];
        }
    }
    return menorElemento;
}

// Retorna o Ã­ndice do maior elemento do vector (assumindo que podemos comparar elementos usando o operador "<")
int vector_argmax(Vector *v){
    int maiorElemento = vector_max(v);

    return vector_find(v, maiorElemento);
}

// Retorna o Ã­ndice do menor elemento do vector (assumindo que podemos comparar elementos usando o operador "<")
int vector_argmin(Vector *v){
    int menorElemento = vector_min(v);

    return vector_find(v, menorElemento);
}

// Remove o i-Ã©simo elemento do vetor.
data_type vector_remove(Vector *v, int i){
    data_type item_removido = v->data[i];

    for(int j = i; j < v->size - 1; j++){
        v->data[j] = v->data[j + 1];
    }

    v->size--;

    return item_removido;
}

// Remove o primeiro elemento
data_type vector_pop_front(Vector *v){
    return vector_remove(v, 0);
}

// Remove o ultimo elemento
data_type vector_pop_back(Vector *v){
    return vector_remove(v, v->size);
}

// Insere o elemento na i-esima posicao
void vector_insert(Vector *v, int i, data_type val){
    if (v->allocated == v->size){
        v->data = (data_type *) realloc(v->data, 2 * sizeof(data_type));
    }
    for (int j = v->size; j > i; j--){
        v->data[j] = v->data[j - 1];
    }

    v->data[i] = val;

    v->size++;
}

// Troca os elementos das posiÃ§Ãµes i e j (i vira j e j vira i)
void vector_swap(Vector *v, int i, int j){
    int aux;
    aux = v->data[i];
    v->data[i] = v->data[j];
    v->data[j] = aux;
}

// Ordena o vetor in-place (sem criar um novo vetor)
void vector_sort(Vector *v) {
    int trocou;
    for (int i = 0; i < v->size - 1; i++) {
        trocou = 0;
        for (int j = 0; j < v->size - i - 1; j++) {
            if (v->data[j] > v->data[j + 1]) {
                vector_swap(v, j, j + 1);
                trocou = 1;
            }
        }
        if (!trocou) {
            break;
        }
    }
}

// Retorna o indice de val usando busca binaria. Retorna -1 se nao encontrado.
int vector_binary_search(Vector *v, data_type val) {
    int baixo = 0;
    int alto = v->size - 1;

    while (baixo <= alto) {
        int meio = baixo + (alto - baixo) / 2;

        if (v->data[meio] == val) {
            return meio;
        } else if (v->data[meio] < val) {
            baixo = meio + 1;
        } else {
            alto = meio - 1;
        }
    }

    return -1;
}

// Inverte o vetor in-place (sem criar um novo vetor)
void vector_reverse(Vector *v){
    int dec = v->size - 1;
    for (int i = 0; i < v->size / 2; i++){
        vector_swap(v, i, dec);
        dec--;
    }

    /* código recomendado:
    for (int i = 0; i < v->size / 2; i++) {
        // (v->size - 1 - i) é o par exato do índice i
        vector_swap(v, i, v->size - 1 - i);
    }
    */
}


void vector_destroy(Vector *v) {
    if (v == NULL) return;
    if (v->data != NULL) {
        free(v->data);
    }
    free(v);
}