#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

typedef struct {
    char nome[33];
    int matriculados;
    int aprovados;
} Disciplina;

typedef struct {
    char nome[33];
    Vector *disciplinas;
    float percentual_reprovacao_medio;
} Professor;

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    Vector *professores = vector_construct();
    float soma_medias_instituicao = 0;

    for (int i = 0; i < n; i++) {
        Professor *p = (Professor *)malloc(sizeof(Professor));
        int m;
        
        scanf("%s %d", p->nome, &m);
        p->disciplinas = vector_construct();
        float soma_percentuais_professor = 0;

        for (int j = 0; j < m; j++) {
            Disciplina *d = (Disciplina *)malloc(sizeof(Disciplina));
            scanf("%s %d %d", d->nome, &d->matriculados, &d->aprovados);
            
            float reprovados = d->matriculados - d->aprovados;
            float percentual_d = reprovados / d->matriculados;
            
            soma_percentuais_professor += percentual_d;
            vector_push_back(p->disciplinas, d);
        }

        if (m > 0) {
            p->percentual_reprovacao_medio = soma_percentuais_professor / m;
        } else {
            p->percentual_reprovacao_medio = 0;
        }

        soma_medias_instituicao += p->percentual_reprovacao_medio;
        vector_push_back(professores, p);
    }

    float media_global = (n > 0) ? (soma_medias_instituicao / n) : 0;

    for (int i = 0; i < vector_size(professores); i++) {
        Professor *p = (Professor *)vector_get(professores, i);
        if (p->percentual_reprovacao_medio > media_global) {
            printf("%s\n", p->nome);
        }
    }

    // Liberação de memória (Respeitando a hierarquia: Disciplinas -> Vetor de Disciplinas -> Professor)
    for (int i = 0; i < vector_size(professores); i++) {
        Professor *p = (Professor *)vector_get(professores, i);
        
        for (int j = 0; j < vector_size(p->disciplinas); j++) {
            free(vector_get(p->disciplinas, j));
        }
        
        vector_destroy(p->disciplinas);
        free(p);
    }
    
    vector_destroy(professores);

    return 0;
}