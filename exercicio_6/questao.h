#ifndef QUESTAO_H
#define QUESTAO_H
 
typedef struct questao Questao;
 
Questao* questao_criar(const char* id, const char* enunciado);
void questao_destruir(Questao* q);
const char* questao_get_id(const Questao* q);
const char* questao_get_enunciado(const Questao* q);
 
#endif