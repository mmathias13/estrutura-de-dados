#include <stdio.h>
#include <stdlib.h>

typedef struct {

    char nome[32];
    float nota_t1;
    float nota_t2;
    float nota_prova;
    float percentual_falta;

} NotasAluno;

float nota_media(NotasAluno a){
    float media = 0;

    return media = ((a.nota_prova + a.nota_t1 + a.nota_t2) / 3.0);
}

int aprovado(NotasAluno a){
    float media = nota_media(a);
    if (media >= 7 && a.percentual_falta <= 0.25){
        return 1;
    } else {
        return 0;
    }
}

int main(int argc, char const *argv[])
{
    NotasAluno aluno;
    scanf("%s", aluno.nome);
    scanf("%f %f %f %f", &aluno.nota_prova, &aluno.nota_t1, &aluno.nota_t2, &aluno.percentual_falta);
    if (aprovado(aluno)){
        printf("APROVADO\n");
    } else {
        printf("REPROVADO\n");
    }
    return 0;
}
