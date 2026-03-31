#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char nome[32];
    float nota_t1;
    float nota_t2;
    float nota_prova;
    float percentual_falta;
} NotasAluno;


int main(){

    NotasAluno aluno;
    scanf("%[^\n]", aluno.nome);
    scanf("%f %f %f %f", &aluno.nota_t1, &aluno.nota_t2, &aluno.nota_prova, &aluno.percentual_falta);
    float media = (float)(aluno.nota_t1 + aluno.nota_t2 + aluno.nota_prova) / 3.0;
    if (media >= 7 && aluno.percentual_falta <= 0.25){
        printf("APROVADO\n");
    } else 
        printf("REPROVADO\n");


    return 0;
}