# Curso de Revisão — Estrutura de Dados: Ponteiros e TADs em C

**Baseado no Plano de Ensino de Programação II / Estrutura de Dados (UFES) — Seções 3 (Ponteiros) e 5 (Tipos Abstratos de Dados)**

## Como usar este material

Este curso assume que você não sabe nada de ponteiros e constrói o conhecimento do zero até o nível cobrado em prova (ponteiro genérico, ponteiro de função, TADs com estrutura opaca). Todo código foi compilado e testado com `gcc -Wall -Wextra`. Leia na ordem — cada seção depende da anterior.

**Sumário:**

1. Módulo 0 — Modelo de memória (pré-requisito)
2. Módulo 1 — Ponteiros do zero ao avançado
3. Módulo 2 — Exercícios resolvidos (lista oficial do professor)
4. Módulo 3 — Tipos Abstratos de Dados (TADs)
5. Módulo 4 — Bateria de exercícios extras + gabarito
6. Módulo 5 — Roteiro de estudo e comandos úteis

---

## Módulo 0 — Modelo de memória (pré-requisito)

Antes de ponteiros fazerem sentido, você precisa de um modelo mental de como a memória funciona.

- Toda variável ocupa um espaço na memória RAM, identificado por um **endereço** (um número, geralmente mostrado em hexadecimal, tipo `0x7ffee23a1c4c`).
- Um programa em C usa basicamente duas regiões de memória para dados: **Stack** (pilha de execução) e **Heap** (memória dinâmica).

| Região | O que armazena | Quem gerencia | Tempo de vida |
|---|---|---|---|
| **Stack** | Variáveis locais, parâmetros de função | Automático (compilador) | Morre quando a função retorna |
| **Heap** | Memória alocada dinamicamente (`malloc`, `calloc`, `realloc`) | Manual (você, com `free`) | Vive até você liberar (ou o programa terminar) |

Um ponteiro nada mais é do que **uma variável cujo valor é um endereço de memória**. Guarde essa frase — ela resolve 80% das dúvidas de quem está começando.

---

## Módulo 1 — Ponteiros do zero ao avançado

### 1.1 O que é um ponteiro

Toda variável tem três coisas: **nome**, **endereço** e **valor**.

```c
int x = 10;
```

| Nome | Endereço (exemplo) | Valor |
|---|---|---|
| `x` | `0x7ffee23a1c4c` | `10` |

Um ponteiro é uma variável que guarda o **endereço** de outra variável, em vez de guardar um valor "normal" (inteiro, float, etc).

```c
int x = 10;
int *p = &x;   // p guarda o ENDEREÇO de x
```

| Nome | Endereço (exemplo) | Valor |
|---|---|---|
| `x` | `0x7ffee23a1c4c` | `10` |
| `p` | `0x7ffee23a1c50` | `0x7ffee23a1c4c` (aponta para `x`) |

### 1.2 Os dois operadores fundamentais

| Operador | Nome | O que faz | Exemplo |
|---|---|---|---|
| `&` | "endereço de" | Retorna o endereço de uma variável | `&x` → endereço de `x` |
| `*` | "conteúdo de" / desreferência | Acessa o valor guardado no endereço apontado | `*p` → valor que está no endereço guardado por `p` |

Regra prática: `*(&x)` é sempre igual a `x`. Um "desfaz" o outro.

```c
#include <stdio.h>

int main(void) {
    int x = 10;
    int *p = &x;

    printf("x = %d\n", x);
    printf("Endereço de x: %p\n", (void*)&x);
    printf("p aponta para: %p\n", (void*)p);
    printf("Valor apontado por p (*p): %d\n", *p);

    *p = 20;   // altera x INDIRETAMENTE, através do ponteiro
    printf("x depois de *p = 20: %d\n", x);

    return 0;
}
```

Saída:
```
x = 10
Endereço de x: 0x...
p aponta para: 0x...
Valor apontado por p (*p): 10
x depois de *p = 20: 20
```

**O pulo do gato:** `p` e `&x` guardam o mesmo valor (o endereço de `x`). Alterar `*p` é o mesmo que alterar `x` diretamente, porque os dois "apontam" para o mesmo espaço na memória.

### 1.3 Declarando ponteiros — cuidado com a sintaxe

Todo ponteiro precisa de um **tipo**, que indica o tipo de dado que ele aponta (isso importa para saber quantos bytes ler/escrever e para permitir aritmética de ponteiros, seção 1.5).

```c
int *p;      // ponteiro para int
float *pf;   // ponteiro para float
char *pc;    // ponteiro para char
double *pd;  // ponteiro para double
```

**Armadilha clássica de prova:** o `*` se associa à **variável**, não ao tipo, quando você declara mais de uma na mesma linha.

```c
int *p1, p2;   // p1 é ponteiro para int. p2 é um int COMUM (não é ponteiro!)
int *p3, *p4;  // p3 e p4 são ambos ponteiros para int
```

Se precisar declarar vários ponteiros na mesma linha, repita o `*` em cada um.

### 1.4 Ponteiro nulo (`NULL`)

Um ponteiro criado sem inicializar aponta para "lixo" — um endereço aleatório. Usar `*p` nesse caso é **comportamento indefinido** (na prática, quase sempre trava o programa: *segmentation fault*).

```c
int *p;        // PERIGO: p aponta para qualquer lugar
*p = 10;       // provável crash
```

Boa prática: sempre inicialize com `NULL` (que representa "não aponta para lugar nenhum") e verifique antes de usar.

```c
int *p = NULL;

if (p != NULL) {
    *p = 10;   // só desreferencia se for seguro
} else {
    printf("p ainda não aponta para nada válido.\n");
}
```

### 1.5 Ponteiros e vetores (aritmética de ponteiros)

Em C, o **nome de um vetor "decai" para um ponteiro** ao endereço do seu primeiro elemento. Isso é a base de tudo:

```c
int vet[5] = {10, 20, 30, 40, 50};
int *p = vet;        // equivalente a: int *p = &vet[0];
```

A partir daí, `vet[i]` e `*(p + i)` são **exatamente equivalentes**. Somar 1 a um ponteiro não soma 1 byte — soma `sizeof(tipo)` bytes, então `p + 1` sempre aponta para o próximo elemento do vetor, seja qual for o tipo.

```c
#include <stdio.h>

int main(void) {
    int vet[5] = {10, 20, 30, 40, 50};
    int *p = vet;

    for (int i = 0; i < 5; i++) {
        printf("vet[%d] = %d | *(p+%d) = %d | endereço = %p\n",
               i, vet[i], i, *(p + i), (void*)(p + i));
    }

    return 0;
}
```

| Notação com colchetes | Notação com ponteiro | Significado |
|---|---|---|
| `vet[i]` | `*(vet + i)` | Valor na posição `i` |
| `&vet[i]` | `vet + i` | Endereço da posição `i` |
| `vet[0]` | `*vet` | Primeiro elemento |

**Diferença importante:** um vetor (`int vet[5]`) tem tamanho fixo e "sabe" seu tamanho (via `sizeof`); um ponteiro (`int *p`) é só um endereço — `sizeof(p)` sempre retorna o tamanho de um ponteiro (8 bytes em máquina 64-bit), não o tamanho do vetor.

### 1.6 Ponteiros e strings

Em C, uma string é um vetor de `char` terminado pelo caractere nulo `'\0'`. Como vetor decai para ponteiro, é comum percorrer strings com ponteiros:

```c
#include <stdio.h>

int main(void) {
    char nome[] = "Matheus";
    char *p = nome;

    while (*p != '\0') {
        printf("%c", *p);
        p++;             // avança para o próximo caractere
    }
    printf("\n");

    return 0;
}
```

`p++` funciona porque `p` é um ponteiro — cada incremento avança 1 `sizeof(char)` = 1 byte, ou seja, o próximo caractere.

### 1.7 Passagem de parâmetros: por valor x por referência

Este é **o principal motivo de existir ponteiro em C**, e cai muito em prova.

Em C, toda passagem de parâmetro é **por valor** — a função recebe uma **cópia**. Alterar a cópia não afeta a variável original.

```c
#include <stdio.h>

void dobra_valor(int x) {      // recebe CÓPIA de a
    x = x * 2;                 // só altera a cópia local
}

void dobra_ref(int *x) {       // recebe o ENDEREÇO de a
    *x = (*x) * 2;             // altera o valor original, via desreferência
}

int main(void) {
    int a = 5;

    dobra_valor(a);
    printf("Após dobra_valor: a = %d\n", a);   // a continua 5

    dobra_ref(&a);
    printf("Após dobra_ref: a = %d\n", a);     // a virou 10

    return 0;
}
```

| Passagem | O que a função recebe | Pode alterar o original? | Sintaxe |
|---|---|---|---|
| Por valor | Cópia do dado | Não | `void f(int x)` |
| Por referência (ponteiro) | Endereço do dado | Sim, via `*` | `void f(int *x)` |

**Regra de ouro:** se a função precisa **devolver mais de um valor** (ex.: calcular área E volume ao mesmo tempo), ela usa ponteiros como parâmetros de saída, já que `return` só devolve um valor.

```c
void calc_esfera(float r, float *area, float *volume) {
    *area   = 4 * 3.14159f * r * r;
    *volume = (4.0f / 3.0f) * 3.14159f * r * r * r;
}

int main(void) {
    float a, v;
    calc_esfera(2.0f, &a, &v);   // passa o ENDEREÇO de a e v
    printf("Área = %.2f, Volume = %.2f\n", a, v);
    return 0;
}
```

Note o padrão: quem **chama** a função passa `&variavel` (endereço); quem **implementa** a função recebe `tipo *parametro` e usa `*parametro` para ler/escrever.

### 1.8 Ponteiro para ponteiro (`int **`)

Se um ponteiro guarda o endereço de uma variável, nada impede que outra variável guarde o endereço **do próprio ponteiro**. Isso é um ponteiro para ponteiro.

```c
#include <stdio.h>

int main(void) {
    int x = 42;
    int *p = &x;     // p aponta para x
    int **pp = &p;   // pp aponta para p

    printf("x    = %d\n", x);
    printf("*p   = %d\n", *p);
    printf("**pp = %d\n", **pp);

    **pp = 100;       // desreferencia duas vezes: pp -> p -> x
    printf("x depois de **pp = 100: %d\n", x);

    return 0;
}
```

Cada `*` "descasca uma camada":

| Expressão | Tipo | Significado |
|---|---|---|
| `pp` | `int**` | Endereço de `p` |
| `*pp` | `int*` | Valor de `p`, ou seja, o endereço de `x` |
| `**pp` | `int` | Valor de `x` |

**Quando isso é usado de verdade:**
1. Quando uma função precisa **alterar um ponteiro que foi passado como parâmetro** (ex.: uma função que aloca memória e precisa "devolver" o novo endereço através do parâmetro — já que ponteiro também é passado por valor).
2. Vetores de ponteiros (`int **vet` pode ser um vetor de ponteiros para int, como na seção 1.9 e no exercício desafio do Módulo 2).

```c
#include <stdio.h>
#include <stdlib.h>

// Função que aloca memória e "devolve" o ponteiro através de outro ponteiro
void aloca_vetor(int **p, int n) {
    *p = (int*) malloc(n * sizeof(int));   // altera o ponteiro do chamador
}

int main(void) {
    int *vet = NULL;
    aloca_vetor(&vet, 5);   // passa o ENDEREÇO do ponteiro

    if (vet != NULL) {
        for (int i = 0; i < 5; i++) vet[i] = i;
        for (int i = 0; i < 5; i++) printf("%d ", vet[i]);
        printf("\n");
        free(vet);
    }

    return 0;
}
```

Sem o `**`, a função `aloca_vetor` receberia uma cópia do ponteiro `vet`; alterar a cópia dentro da função não mudaria o `vet` de `main` (mesmo problema da seção 1.7, só que com ponteiros no lugar de `int`).

### 1.9 Ponteiro genérico (`void *`)

`void *` é um ponteiro que **não tem tipo definido** — ele guarda um endereço, mas não sabe (e não diz ao compilador) que tipo de dado está lá. Serve para escrever funções genéricas, que funcionam com qualquer tipo de dado.

Regras de `void*`:
- Não pode ser desreferenciado diretamente (`*p` não compila se `p` é `void*`) — primeiro é preciso converter (*cast*) para um tipo concreto.
- Qualquer ponteiro pode ser atribuído a um `void*` sem cast explícito, e vice-versa.

```c
#include <stdio.h>

void imprime_int(void *dado) {
    int *p = (int*) dado;     // cast: "trate esse endereço como int*"
    printf("%d\n", *p);
}

void imprime_float(void *dado) {
    float *p = (float*) dado;
    printf("%.2f\n", *p);
}

int main(void) {
    int i = 10;
    float f = 3.14f;

    imprime_int(&i);
    imprime_float(&f);

    return 0;
}
```

`void*` é a base da **genericidade** em C: como a linguagem não tem "templates" (como C++), é assim que se escrevem estruturas de dados que guardam "qualquer tipo" — veremos isso de novo no TAD Pilha genérica (Módulo 3).

### 1.10 Alocação dinâmica de memória

Até aqui, todo espaço de memória usado era alocado automaticamente pelo compilador (stack). Alocação dinâmica pede memória **na Heap**, em tempo de execução, quando você não sabe o tamanho necessário em tempo de compilação (ex.: tamanho de vetor definido pelo usuário).

| Função | O que faz | Inicializa com zero? |
|---|---|---|
| `malloc(n)` | Aloca `n` bytes | Não (lixo de memória) |
| `calloc(n, tam)` | Aloca `n` elementos de `tam` bytes cada | Sim |
| `realloc(p, novo_tam)` | Redimensiona um bloco já alocado | Mantém o conteúdo existente |
| `free(p)` | Libera a memória apontada por `p` | — |

```c
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n = 5;
    int *vet = (int*) malloc(n * sizeof(int));   // pede espaço para 5 int's

    if (vet == NULL) {                // malloc pode falhar (memória cheia)
        printf("Erro: sem memória!\n");
        return 1;
    }

    for (int i = 0; i < n; i++) vet[i] = i * i;
    for (int i = 0; i < n; i++) printf("%d ", vet[i]);
    printf("\n");

    free(vet);     // devolve a memória ao sistema
    vet = NULL;    // boa prática: evita "ponteiro solto" (dangling pointer)

    return 0;
}
```

**Por que sempre `sizeof(tipo)`?** Porque o tamanho de `int`, `float`, `struct X` etc. pode variar entre plataformas — `malloc(n * sizeof(int))` é portável; `malloc(n * 4)` não é.

`realloc` na prática (crescer um vetor dinamicamente):

```c
int *vet = (int*) malloc(2 * sizeof(int));
vet[0] = 1; vet[1] = 2;

// preciso de mais espaço:
int *tmp = (int*) realloc(vet, 4 * sizeof(int));
if (tmp == NULL) {
    // realloc falhou: vet ORIGINAL ainda é válido, não foi perdido
    free(vet);
} else {
    vet = tmp;         // só reatribui se deu certo
    vet[2] = 3; vet[3] = 4;
}
```

**Regra de ouro da alocação dinâmica:** para todo `malloc`/`calloc`, deve existir exatamente um `free` correspondente. Duas violações clássicas:

| Erro | O que é | Consequência |
|---|---|---|
| **Memory leak** (vazamento) | Alocou e nunca deu `free` | Programa consome memória até travar/lentidão |
| **Dangling pointer** | Usar um ponteiro depois do `free` | Comportamento indefinido, bugs difíceis de rastrear |
| **Double free** | Dar `free` duas vezes no mesmo ponteiro | Corrompe o alocador de memória, crash |

### 1.11 Ponteiro de função

Assim como uma variável guarda o endereço de um dado, um ponteiro de função guarda o **endereço de uma função**. Isso permite passar comportamento (não só dados) como parâmetro — a base de callbacks e de código genérico.

```c
#include <stdio.h>

int soma(int a, int b) { return a + b; }
int sub(int a, int b)  { return a - b; }

// aplica recebe QUALQUER função com assinatura (int, int) -> int
int aplica(int a, int b, int (*op)(int, int)) {
    return op(a, b);
}

int main(void) {
    int (*p_op)(int, int);   // declara um ponteiro para função (int,int)->int

    p_op = soma;
    printf("soma: %d\n", aplica(5, 3, p_op));

    p_op = sub;
    printf("sub: %d\n", aplica(5, 3, p_op));

    // também dá para passar a função diretamente, sem variável intermediária:
    printf("soma direta: %d\n", aplica(10, 20, soma));

    return 0;
}
```

Como ler a declaração `int (*op)(int, int)`:
- `op` é um ponteiro (`*op`)
- que aponta para algo que recebe `(int, int)`
- e retorna `int`

Os parênteses em `(*op)` são obrigatórios — sem eles, `int *op(int, int)` seria lido como "função que retorna `int*`", algo completamente diferente.

**Onde isso aparece de verdade:** funções da biblioteca padrão como `qsort` usam ponteiro de função para comparar elementos de qualquer tipo; TADs genéricos usam ponteiro de função para permitir que quem usa a estrutura defina como comparar/liberar/imprimir seus próprios dados (ver Módulo 3.5).

### 1.12 Erros clássicos com ponteiros (o que evitar em prova e no TP)

| Erro | Exemplo | Por que é grave |
|---|---|---|
| Ponteiro não inicializado | `int *p; *p = 5;` | `p` aponta para lixo → crash imprevisível |
| Desreferenciar `NULL` | `int *p = NULL; *p = 5;` | Crash garantido (segmentation fault) |
| Dangling pointer | Usar `p` depois de `free(p)` | Memória já pode ter sido reaproveitada por outra coisa |
| Memory leak | `malloc` sem `free` correspondente | Consumo de memória cresce sem parar |
| Buffer overflow | Escrever em `vet[n]` quando o vetor tem tamanho `n` (índice válido: `0..n-1`) | Corrompe memória vizinha, comportamento indefinido |
| Confundir `&` com `*` | Trocar `scanf("%d", p)` por `scanf("%d", &p)` quando `p` já é `int*` | Lê valor no endereço errado |
| `int *p1, p2;` achando que os dois são ponteiros | Ver seção 1.3 | `p2` não é ponteiro, é `int` |

### 1.13 Cheat sheet — resumo de ponteiros

| Você quer... | Sintaxe |
|---|---|
| Declarar um ponteiro para `int` | `int *p;` |
| Pegar o endereço de uma variável | `&variavel` |
| Ler/escrever o valor apontado | `*p` |
| Apontar `p` para `x` | `p = &x;` |
| Passar `x` por referência para uma função | Parâmetro `int *x`, chamada `f(&x)` |
| Percorrer um vetor com ponteiro | `for (int *p = vet; p < vet + n; p++)` |
| Alocar `n` inteiros dinamicamente | `int *v = malloc(n * sizeof(int));` |
| Liberar memória alocada | `free(v); v = NULL;` |
| Ponteiro para ponteiro | `int **pp = &p;` |
| Ponteiro genérico (aceita qualquer tipo) | `void *p;` (precisa de cast para usar) |
| Ponteiro de função `(int,int)->int` | `int (*op)(int, int);` |

---

## Módulo 2 — Exercícios resolvidos (lista oficial do professor)

Resolução comentada da lista "Exercício de Revisão de Ponteiros em C". Todos os testes abaixo foram compilados e executados; as saídas mostradas são reais.

### 2.1 Área e volume de esfera (2 saídas via ponteiro)

```c
void calc_esfera(float r, float *area, float *volume) {
    *area   = 4 * 3.14159f * r * r;
    *volume = (4.0f / 3.0f) * 3.14159f * r * r * r;
}
```

**Ideia central:** `return` só devolve um valor. Para devolver `area` E `volume`, a função recebe dois ponteiros de saída e escreve os resultados neles com `*area = ...` e `*volume = ...`. Quem chama passa `&area` e `&volume`.

### 2.2 Raízes de equação do 2º grau (retorno indica sucesso, ponteiros trazem o resultado)

```c
int raizes(float a, float b, float c, float *x1, float *x2) {
    if (a == 0) return 0;              // não é do 2º grau

    float delta = b*b - 4*a*c;
    if (delta < 0) return 0;           // sem raízes reais

    *x1 = (-b + sqrtf(delta)) / (2*a);
    *x2 = (-b - sqrtf(delta)) / (2*a);
    return 1;                          // sucesso
}
```

**Padrão importante:** `int` como retorno é usado como "código de sucesso" (1 = achou raízes, 0 = não achou), enquanto os valores em si saem pelos ponteiros `x1` e `x2`. Esse padrão (retorno = status, ponteiro = dado) é extremamente comum em C. Compilar com `-lm` (biblioteca matemática, por causa do `sqrtf`).

### 2.3 Conta números pares em um vetor (ponteiro como vetor de entrada)

```c
int pares(int n, int *vet) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (vet[i] % 2 == 0) count++;
    }
    return count;
}
```

Aqui `int *vet` recebe o vetor decaído para ponteiro (seção 1.5) — dentro da função, `vet[i]` funciona normalmente porque `vet[i]` e `*(vet+i)` são a mesma coisa.

### 2.4 Inverte um vetor in-place (ponteiro como vetor de entrada e saída)

```c
void inverte(int n, int *vet) {
    int i = 0, j = n - 1;
    while (i < j) {
        int tmp = vet[i];
        vet[i] = vet[j];
        vet[j] = tmp;
        i++;
        j--;
    }
}
```

Não há `return`: como `vet` é um ponteiro para o vetor original, alterar `vet[i]` dentro da função já altera o vetor de quem chamou — não é preciso devolver nada.

### 2.5 Avaliação de polinômios (vetor de coeficientes)

```c
double avalia(double *poli, int grau, double x) {
    double resultado = 0;
    for (int i = 0; i <= grau; i++) {
        double termo = poli[i];
        for (int j = 0; j < i; j++) termo *= x;   // termo = poli[i] * x^i
        resultado += termo;
    }
    return resultado;
}
```

Teste: para `3x² + 2x + 12` (`poli = {12, 2, 3}`, `grau = 2`), em `x = 2`: `12 + 2·2 + 3·4 = 12 + 4 + 12 = 28`. Confirmado na execução.

### 2.6 DESAFIO — vetor de ponteiros ordenado (`int**`)

```c
int** inverte2(int n, int *vet) {
    int **ordenado = (int**) malloc(n * sizeof(int*));   // vetor de PONTEIROS
    if (ordenado == NULL) return NULL;

    // cada posição guarda o ENDEREÇO do elemento correspondente em vet
    for (int i = 0; i < n; i++) {
        ordenado[i] = &vet[i];
    }

    // bubble sort: compara os VALORES apontados, mas troca os PONTEIROS
    // (o vetor original 'vet' nunca é alterado)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (*ordenado[j] > *ordenado[j+1]) {
                int *tmp = ordenado[j];
                ordenado[j] = ordenado[j+1];
                ordenado[j+1] = tmp;
            }
        }
    }

    return ordenado;
}
```

**Por que `int**` e não `int*`?** A função precisa retornar um **vetor de endereços** (cada posição é um `int*`), não um vetor de inteiros. Um vetor de ponteiros para `int` é, por definição, `int**` (ponteiro para ponteiro para int — o primeiro `*` indexa o vetor, o segundo desreferencia até o inteiro).

Teste com `vet = {5, 2, 8, 1, 9}`: o resultado impresso (`*ord[i]` para cada `i`) foi `1 2 5 8 9` — os valores originais, em ordem crescente, sem que `vet` tenha sido modificado.

**Atenção ao `free`:** só é preciso `free(ordenado)` — o vetor de ponteiros. Os inteiros apontados pertencem ao vetor original `vet` (que não foi alocado dinamicamente nesse teste), então não devem ser liberados individualmente.

---

## Módulo 3 — Tipos Abstratos de Dados (TADs)

### 3.1 O que é um TAD e por que usar

Um **Tipo Abstrato de Dados (TAD)** é a definição de um tipo de dado **pelo comportamento**, não pela implementação: um conjunto de operações permitidas (`cria`, `insere`, `remove`, `consulta`...) e as regras que elas seguem, sem expor **como** os dados estão organizados por dentro.

Analogia: para usar um carro você usa volante, pedais e câmbio (a **interface**). Não precisa saber como o motor funciona por dentro (a **implementação**) para dirigir. Se o fabricante trocar o motor por um mais eficiente, você continua dirigindo do mesmo jeito.

| Conceito | Definição |
|---|---|
| **Interface** | O conjunto de operações públicas que o TAD oferece (o "contrato") |
| **Implementação** | Como os dados são realmente guardados e como as operações funcionam por dentro |
| **Encapsulamento** | Esconder a implementação, expondo só a interface — quem usa o TAD não pode (nem precisa) mexer diretamente nos dados internos |

Por que isso importa na prática: você pode **trocar a implementação** de um TAD (ex.: de vetor para lista encadeada) sem que o código que o utiliza precise mudar uma linha — desde que a interface continue a mesma. É a mesma ideia usada por toda a biblioteca padrão de qualquer linguagem.

### 3.2 Separação interface/implementação: arquivos `.h` e `.c`

Em C, o TAD é dividido em (pelo menos) dois arquivos:

| Arquivo | Contém | Quem lê |
|---|---|---|
| `nome.h` (header) | Declaração do tipo e **protótipos** das funções (a interface) | Quem *usa* o TAD |
| `nome.c` | Implementação das funções (os detalhes internos) | Só o compilador (e quem mantém o TAD) |

Exemplo — TAD `Ponto`:

**`ponto.h`**
```c
#ifndef PONTO_H
#define PONTO_H

typedef struct Ponto Ponto;   // tipo declarado, mas NÃO definido aqui (ver 3.3)

Ponto* ponto_cria(float x, float y);
void   ponto_destroi(Ponto *p);
float  ponto_get_x(const Ponto *p);
float  ponto_get_y(const Ponto *p);
void   ponto_set(Ponto *p, float x, float y);
float  ponto_distancia(const Ponto *p1, const Ponto *p2);

#endif
```

`#ifndef`/`#define`/`#endif` é o **include guard** — evita que o mesmo `.h` seja incluído duas vezes no mesmo arquivo (o que causaria erro de redefinição).

**`ponto.c`**
```c
#include <stdlib.h>
#include <math.h>
#include "ponto.h"

struct Ponto {        // definição REAL só existe aqui
    float x;
    float y;
};

Ponto* ponto_cria(float x, float y) {
    Ponto *p = (Ponto*) malloc(sizeof(Ponto));
    if (p != NULL) {
        p->x = x;
        p->y = y;
    }
    return p;
}

void ponto_destroi(Ponto *p) { free(p); }

float ponto_get_x(const Ponto *p) { return p->x; }
float ponto_get_y(const Ponto *p) { return p->y; }

void ponto_set(Ponto *p, float x, float y) {
    p->x = x;
    p->y = y;
}

float ponto_distancia(const Ponto *p1, const Ponto *p2) {
    float dx = p1->x - p2->x;
    float dy = p1->y - p2->y;
    return sqrtf(dx*dx + dy*dy);
}
```

**`main.c`** (quem usa o TAD)
```c
#include <stdio.h>
#include "ponto.h"

int main(void) {
    Ponto *a = ponto_cria(0, 0);
    Ponto *b = ponto_cria(3, 4);

    printf("Distância: %.2f\n", ponto_distancia(a, b));

    ponto_set(a, 1, 1);
    printf("a = (%.1f, %.1f)\n", ponto_get_x(a), ponto_get_y(a));

    ponto_destroi(a);
    ponto_destroi(b);
    return 0;
}
```

Compilação em separado (uma unidade por arquivo, depois "linkadas"):
```
gcc -Wall -Wextra -c ponto.c -o ponto.o
gcc -Wall -Wextra -c main.c  -o main.o
gcc ponto.o main.o -o prog -lm
```

Saída real (testado):
```
Distância: 5.00
a = (1.0, 1.0)
```

### 3.3 Estrutura opaca (Opaque Struct) — o mecanismo de encapsulamento em C

Repare em `ponto.h`: `typedef struct Ponto Ponto;` declara que existe um tipo `Ponto`, mas **não diz quais campos ele tem**. A definição completa (`struct Ponto { float x; float y; };`) só aparece dentro de `ponto.c`.

Isso se chama **estrutura opaca**: para quem inclui só o `.h`, `Ponto` é um **tipo incompleto** — o compilador sabe que ele existe (então pode manipular ponteiros `Ponto*`), mas não sabe seu tamanho nem seus campos, então **não permite acessar `p->x` diretamente** fora de `ponto.c`.

Testando isso na prática, este código **não compila**:

```c
#include "ponto.h"

int main(void) {
    Ponto *a = ponto_cria(0, 0);
    printf("%f\n", a->x);   // ERRO
    return 0;
}
```

Erro real do `gcc`:
```
error: invalid use of incomplete typedef 'Ponto'
```

Esse erro é a prova de que o encapsulamento está funcionando: a única forma de ler ou alterar `x` é através das funções que `ponto.h` disponibiliza (`ponto_get_x`, `ponto_set`, ...). Ninguém "de fora" consegue violar as regras internas do TAD.

| Sem estrutura opaca | Com estrutura opaca |
|---|---|
| `struct Ponto` definido no `.h` | `struct Ponto` definido só no `.c` |
| Qualquer código pode fazer `p->x = -999` (bypassa validações) | Só as funções do próprio TAD acessam os campos |
| Mudar a implementação (ex.: trocar `float` por `double`) quebra quem usa `p->x` | Mudar a implementação não afeta quem usa o TAD, pois ninguém depende da estrutura interna |

### 3.4 Tipos genéricos em TADs

O `TAD Ponto` guarda só `float`. Para um TAD reutilizável com **qualquer tipo de dado** (inteiro, struct, string...), usa-se `void*` como visto na seção 1.9 — o TAD guarda **endereços genéricos**, e quem usa o TAD é responsável por fazer o cast de volta ao tipo certo.

**`pilha.h`**
```c
#ifndef PILHA_H
#define PILHA_H

typedef struct Pilha Pilha;

Pilha* pilha_cria(void);
int    pilha_vazia(const Pilha *p);
void   pilha_empilha(Pilha *p, void *dado);
void*  pilha_desempilha(Pilha *p);
void*  pilha_topo(const Pilha *p);
void   pilha_destroi_completa(Pilha *p, void (*libera)(void*));   // ver 3.5

#endif
```

**`pilha.c`** (implementação encadeada, com nó opaco)
```c
#include <stdlib.h>
#include "pilha.h"

typedef struct No {
    void *dado;
    struct No *prox;
} No;

struct Pilha {
    No *topo;
    int tamanho;
};

Pilha* pilha_cria(void) {
    Pilha *p = (Pilha*) malloc(sizeof(Pilha));
    if (p != NULL) { p->topo = NULL; p->tamanho = 0; }
    return p;
}

int pilha_vazia(const Pilha *p) { return p->topo == NULL; }

void pilha_empilha(Pilha *p, void *dado) {
    No *novo = (No*) malloc(sizeof(No));
    novo->dado = dado;
    novo->prox = p->topo;
    p->topo = novo;
    p->tamanho++;
}

void* pilha_desempilha(Pilha *p) {
    if (pilha_vazia(p)) return NULL;
    No *removido = p->topo;
    void *dado = removido->dado;
    p->topo = removido->prox;
    free(removido);
    p->tamanho--;
    return dado;
}

void* pilha_topo(const Pilha *p) {
    if (pilha_vazia(p)) return NULL;
    return p->topo->dado;
}
```

Note que `dado` é `void*` em toda a interface: essa **mesma pilha** serve para guardar `int*`, `Pessoa*`, `char*` ou qualquer outro ponteiro, sem reescrever uma linha de código.

### 3.5 Ponteiro de funções em TADs

Um TAD genérico às vezes precisa executar uma operação **definida por quem o usa**, não por quem o implementou — por exemplo: como liberar um dado genérico (`void*`) ao destruir a pilha? O TAD não sabe se aquele `void*` é um `int*` (basta `free`) ou uma `Pessoa*` (talvez precise fechar um arquivo antes, imprimir um log, etc). A solução é receber essa operação como **ponteiro de função** (callback):

```c
void pilha_destroi_completa(Pilha *p, void (*libera)(void*)) {
    while (!pilha_vazia(p)) {
        void *dado = pilha_desempilha(p);
        if (libera != NULL) libera(dado);   // quem chamou decide como liberar
    }
    free(p);
}
```

Uso com dois tipos de dado diferentes, cada um com sua própria função de liberação:

```c
#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

typedef struct {
    char nome[20];
    int idade;
} Pessoa;

void libera_int(void *dado) {
    free(dado);
}

void libera_pessoa(void *dado) {
    Pessoa *p = (Pessoa*) dado;
    printf("Liberando pessoa: %s\n", p->nome);
    free(p);
}

int main(void) {
    // Pilha de inteiros alocados dinamicamente
    Pilha *pi = pilha_cria();
    for (int i = 1; i <= 3; i++) {
        int *v = malloc(sizeof(int));
        *v = i * 10;
        pilha_empilha(pi, v);
    }
    printf("Topo da pilha de int: %d\n", *(int*)pilha_topo(pi));
    pilha_destroi_completa(pi, libera_int);        // <- comportamento injetado

    // Pilha de structs Pessoa (MESMO TAD, dado diferente)
    Pilha *pp = pilha_cria();
    Pessoa *m = malloc(sizeof(Pessoa));
    snprintf(m->nome, 20, "Matheus");
    m->idade = 23;
    pilha_empilha(pp, m);

    Pessoa *topo = (Pessoa*) pilha_topo(pp);
    printf("Topo da pilha de pessoas: %s, %d anos\n", topo->nome, topo->idade);

    pilha_destroi_completa(pp, libera_pessoa);     // <- outro comportamento injetado

    return 0;
}
```

Saída real (testado):
```
Topo da pilha de int: 30
Topo da pilha de pessoas: Matheus, 23 anos
Liberando pessoa: Matheus
```

**O ponto-chave:** o TAD `Pilha` foi escrito **uma única vez** e serve para qualquer tipo de dado (genericidade via `void*`, seção 3.4) e para qualquer política de liberação de memória (genericidade de comportamento via ponteiro de função, esta seção). É exatamente isso que o plano de ensino chama de "5.2 Tipos genéricos" e "5.3 Ponteiro de Funções em TADs".

Outro exemplo clássico do mesmo padrão — busca genérica em vetor, combinando `void*` (dado genérico) com ponteiro de função (comparador genérico), no mesmo espírito de `qsort`/`bsearch` da biblioteca padrão:

```c
#include <stdio.h>

typedef int (*FuncCompara)(const void*, const void*);

int busca_generica(void *vet, int n, size_t tam_elem, void *chave, FuncCompara compara) {
    char *base = (char*) vet;              // aritmética de ponteiro byte a byte
    for (int i = 0; i < n; i++) {
        void *elem = base + i * tam_elem;  // endereço do i-ésimo elemento
        if (compara(elem, chave) == 0) return i;
    }
    return -1;
}

int compara_int(const void *a, const void *b) {
    int x = *(const int*)a;
    int y = *(const int*)b;
    return x - y;
}

int main(void) {
    int vet[] = {5, 2, 8, 1, 9};
    int chave = 8;

    int pos = busca_generica(vet, 5, sizeof(int), &chave, compara_int);
    printf("Posição de %d: %d\n", chave, pos);   // Posição de 8: 2

    return 0;
}
```

`busca_generica` funciona para **qualquer tipo** de vetor (`int`, `float`, `struct`...) — basta passar o `tam_elem` certo (`sizeof(tipo)`) e a função de comparação adequada. Isso é o mesmo mecanismo por trás de `qsort` e `bsearch` da biblioteca padrão de C.

### 3.6 Checklist mental para montar qualquer TAD em prova

1. Defina a **interface** primeiro: quais operações o TAD precisa oferecer? (`.h`)
2. Torne a struct **opaca**: `typedef struct X X;` no `.h`, `struct X { ... };` só no `.c`.
3. Toda função que **cria** aloca com `malloc`; toda função que **destrói** dá `free`.
4. Se o TAD precisa guardar qualquer tipo de dado → campo `void*` + funções `void*` na interface.
5. Se o TAD precisa de comportamento customizável (comparar, liberar, imprimir) → parâmetro de ponteiro de função.
6. Funções que só leem (não alteram) devem receber `const Tipo *` — protege contra alteração acidental e documenta a intenção.

---

## Módulo 4 — Bateria de exercícios extras (com gabarito)

Tente resolver cada questão **antes** de olhar o gabarito no final da seção. São questões no estilo do que costuma cair em prova de Estrutura de Dados/Programação II.

**Conceituais**

1. Qual a diferença entre `int *p` e `int **p`? Dê um exemplo de quando usar cada um.
2. Por que `scanf("%d", &x)` usa `&`, mas `scanf("%s", nome)` (para `char nome[20]`) não usa?
3. O que acontece se você der `free(p)` duas vezes seguidas no mesmo ponteiro?
4. Explique por que `int *p1, p2;` é uma armadilha comum, e o que `p2` realmente é.
5. O que é uma estrutura opaca e qual problema ela resolve?

**Código — complete ou corrija**

6. A função abaixo deveria trocar os valores de `a` e `b`, mas tem um bug. Encontre e corrija:
```c
void troca(int a, int b) {
    int tmp = a;
    a = b;
    b = tmp;
}
```

7. Complete a função `soma_vetor` para que retorne a soma de todos os elementos de `vet` (tamanho `n`), usando aritmética de ponteiros (sem usar `vet[i]`):
```c
int soma_vetor(int *vet, int n) {
    int soma = 0;
    // seu código aqui, usando *(vet + i) ou incrementando um ponteiro
    return soma;
}
```

8. O código abaixo tem um vazamento de memória (*memory leak*). Onde, e como corrigir?
```c
void processa(int n) {
    int *vet = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) vet[i] = i;
    if (vet[0] == 0) {
        return;   // bug aqui
    }
    free(vet);
}
```

9. Escreva um TAD mínimo `Contador` com estrutura opaca, com as operações: `contador_cria()`, `contador_incrementa(Contador *c)`, `contador_valor(const Contador *c)`, `contador_destroi(Contador *c)`. (Só a interface `.h` já é suficiente para a resposta.)

10. Escreva uma função `int** aloca_matriz(int linhas, int colunas)` que aloca dinamicamente uma matriz de inteiros usando `malloc` (vetor de ponteiros, cada um apontando para uma linha alocada separadamente). Escreva também `void libera_matriz(int **m, int linhas)` para desalocar corretamente.

---

### Gabarito comentado

**1.** `int *p` guarda o endereço de um `int` (uma "camada" de indireção). `int **p` guarda o endereço de um `int*` (duas camadas). Use `int*` para passar uma variável por referência (seção 1.7); use `int**` quando a própria função precisa alterar um ponteiro do chamador (ex.: uma função que aloca memória e "devolve" o novo ponteiro — seção 1.8) ou para representar um vetor de ponteiros (ex.: matriz dinâmica, questão 10).

**2.** `scanf` sempre precisa de um **endereço** para escrever o valor lido. Uma variável `int x` não é um endereço, então precisa de `&x`. Já `nome` (um vetor `char[20]`) **já decai automaticamente para um ponteiro** (endereço do primeiro elemento — seção 1.5), então `&nome` estaria "endereçando um endereço" desnecessariamente (tecnicamente teria tipo diferente, `char(*)[20]`, o que causaria warning/erro).

**3.** *Double free* — comportamento indefinido. Na prática, corrompe as estruturas internas do alocador de memória e costuma causar crash (às vezes imediato, às vezes bem depois, o que torna difícil de depurar). Regra: sempre coloque `p = NULL` depois de `free(p)`; `free(NULL)` é seguro (não faz nada), então um segundo `free` acidental não quebra o programa.

**4.** Em C, o `*` na declaração se associa a cada **identificador**, não ao tipo da linha inteira. Em `int *p1, p2;`, só `p1` é ponteiro; `p2` é um `int` comum. Para declarar dois ponteiros na mesma linha, é preciso repetir o `*`: `int *p1, *p2;`.

**5.** Estrutura opaca é uma struct cuja definição completa só existe no `.c` de implementação; no `.h`, aparece só como `typedef struct X X;` (tipo incompleto). Isso impede que código externo acesse os campos diretamente (`p->campo` não compila fora do `.c`), forçando todo acesso a passar pelas funções da interface — é o mecanismo de **encapsulamento** de C (seção 3.3).

**6.** `troca` recebe `a` e `b` **por valor** — troca só as cópias locais, sem efeito fora da função. Correção: receber ponteiros.
```c
void troca(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
// chamada: troca(&x, &y);
```

**7.**
```c
int soma_vetor(int *vet, int n) {
    int soma = 0;
    for (int i = 0; i < n; i++) {
        soma += *(vet + i);
    }
    return soma;
}
```

**8.** O `return` dentro do `if` sai da função **antes** do `free(vet)`, então, se `vet[0] == 0`, a memória alocada nunca é liberada. Correção: liberar antes de qualquer `return`, ou usar um único ponto de saída:
```c
void processa(int n) {
    int *vet = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) vet[i] = i;
    if (vet[0] == 0) {
        free(vet);   // libera antes de sair
        return;
    }
    free(vet);
}
```

**9.**
```c
#ifndef CONTADOR_H
#define CONTADOR_H

typedef struct Contador Contador;

Contador* contador_cria(void);
void      contador_incrementa(Contador *c);
int       contador_valor(const Contador *c);
void      contador_destroi(Contador *c);

#endif
```
Implementação (`.c`) teria `struct Contador { int valor; };` e cada função manipulando esse campo — mas quem usa o TAD nunca vê `struct Contador` por dentro, só as quatro funções acima.

**10.**
```c
int** aloca_matriz(int linhas, int colunas) {
    int **m = (int**) malloc(linhas * sizeof(int*));
    if (m == NULL) return NULL;

    for (int i = 0; i < linhas; i++) {
        m[i] = (int*) malloc(colunas * sizeof(int));
    }
    return m;
}

void libera_matriz(int **m, int linhas) {
    for (int i = 0; i < linhas; i++) {
        free(m[i]);   // libera cada linha primeiro
    }
    free(m);          // depois libera o vetor de ponteiros
}
```
Erro comum: liberar `m` antes das linhas (`free(m)` primeiro) — isso perde os ponteiros das linhas antes de liberá-las, causando *memory leak* de todas as linhas.

---

## Módulo 5 — Roteiro de estudo e comandos úteis

### 5.1 Mapa: Plano de Ensino → este curso

| Item do plano de ensino | Onde estudar aqui |
|---|---|
| 3.1 Definição e uso de ponteiros | Módulo 1, seções 1.1 – 1.7 |
| 3.2 Ponteiro genérico | Módulo 1, seção 1.9 |
| 3.3 Passagem de parâmetros | Módulo 1, seção 1.7 |
| 3.4 Ponteiro de funções | Módulo 1, seção 1.11 |
| 4.1 – 4.2 Alocação estática/dinâmica, manipulação de ponteiros | Módulo 1, seção 1.10 |
| 4.3 Ferramentas de detecção de erros | Módulo 5, seção 5.3 (Valgrind) |
| 5.1 Estrutura opaca | Módulo 3, seção 3.3 |
| 5.2 Tipos genéricos | Módulo 3, seção 3.4 |
| 5.3 Ponteiro de Funções em TADs | Módulo 3, seção 3.5 |

### 5.2 Sugestão de ordem de estudo (revisão em 1 semana)

| Dia | Foco | Ação |
|---|---|---|
| 1 | Módulo 0 + 1.1–1.6 | Ler e digitar/rodar cada exemplo você mesmo (não só ler) |
| 2 | 1.7–1.9 (referência, `void*`) | Refazer os exemplos sem olhar o gabarito |
| 3 | 1.10–1.13 (alocação dinâmica, cheat sheet) | Rodar os exemplos com Valgrind (seção 5.3) |
| 4 | Módulo 2 completo | Resolver a lista original do professor do zero, comparar com a resolução |
| 5 | Módulo 3 (3.1–3.4) | Implementar o TAD `Ponto` e o TAD `Pilha` você mesmo, em arquivos separados |
| 6 | Módulo 3 (3.5–3.6) | Implementar `pilha_destroi_completa` e a busca genérica |
| 7 | Módulo 4 | Resolver as 10 questões sem consultar o gabarito, depois conferir |

### 5.3 Comandos úteis para compilar e depurar em C

| Comando | O que faz |
|---|---|
| `gcc -Wall -Wextra -o prog prog.c` | Compila com avisos extras ligados (pega a maioria dos erros bobos com ponteiros) |
| `gcc -Wall -Wextra -g -o prog prog.c` | Idem, com símbolos de debug (`-g`) para usar com `gdb` |
| `gcc arq1.c arq2.c -o prog` | Compila e "linka" múltiplos arquivos `.c` de um TAD |
| `gcc -c arq.c -o arq.o` | Compila em separado, gerando só o objeto (sem linkar ainda) |
| `valgrind --leak-check=full ./prog` | Detecta memory leaks, dangling pointers e acessos inválidos |
| `gdb ./prog` | Depurador interativo (útil para achar exatamente onde ocorre um segfault) |

**Dica prática:** rode `valgrind --leak-check=full ./prog` em qualquer programa que use `malloc`/`free` antes de entregar um trabalho — ele aponta exatamente qual `malloc` nunca teve seu `free` correspondente.

---

**Próximos passos:** este curso cobriu os itens 3 e 5 do plano de ensino (Ponteiros e TADs). Se quiser, posso montar o mesmo tipo de material para Modularização (item 2, `.h`/Makefile), Uso eficiente de memória (item 4) ou Arquivos (item 6) — é só pedir.