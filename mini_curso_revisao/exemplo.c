#include <stdio.h>
#include <stdlib.h>

int contaTamanhoString(char *s){
    int n = 0;
    for (int i = 0; s[i] != '\0'; i++){
        n++;
    }
    return n;
}

void copia (char *origem, char *destino){
    int i = 0;
    for (i = 0; origem[i] != '\0'; i++){
        destino[i] = origem[i];
    }
    destino[i] = '\0';
}

void concatena(char *s){
    for (int i = 0; s[i] != '\0'; i++){
        if (s[i] == ' '){
            for (int j = i; s[j] != '\0'; j++){
                s[j] = s[j + 1];
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    /* TESTE STRLEN
    int n = 0;
    scanf("%d", &n);
    char *string = (char*)malloc(n * sizeof(char));
    scanf("%[^\n]", string);
    int tam = contaTamanhoString(string);
    printf("Tamanho da string: %d\n", tam);
    free(string);
    */


    /* TESTE STRCPY
    char origem[100] = "Olá";
    char destino[100] = "Oiiii";
    printf("Origem antes: %s\n", origem);
    printf("Destino antes: %s\n", destino);
    copia(origem, destino);
    printf("Destino depois: %s\n", destino); 
    */

    char stringSolta[100] = "STRING COM ESPAÇOS";
    printf("String antes: %s\n", stringSolta);
    concatena(stringSolta);
    printf("String depois: %s\n", stringSolta);
    return 0;
}
