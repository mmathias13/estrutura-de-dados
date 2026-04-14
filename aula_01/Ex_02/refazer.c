#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    
    char nome[32];
    float nota_t1;
    float nota_t2;
    float nota_prova;
    float percentual_falta;

}NotasAluno;

float nota_media(NotasAluno aluno){

    float media = (float) (aluno.nota_prova + aluno.nota_t1 + aluno.nota_t2) / 3.0;


    return media;
}

void aprovado(NotasAluno aluno){
    if (aluno.percentual_falta <= 0.25 && nota_media(aluno)){
        printf("APROVADO\n");
    } else {
        printf("REPROVADO\n");
    }
}

int main(int argc, char const *argv[])
{
    NotasAluno aluno;

    scanf("%s\n%f %f %f %f", aluno.nome, &aluno.nota_t1, &aluno.nota_t2, &aluno.nota_prova, &aluno.percentual_falta);

    aprovado(aluno);
    
    return 0;
}
