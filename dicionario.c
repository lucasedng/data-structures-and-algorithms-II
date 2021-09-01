//Lucas Eduardo Nogueira Gonçalves, 122055 (Integral)
#include <stdio.h>
#include <stdlib.h>
#define NIL -1

void ImprimeVetor(int n, int *vet) /* função que imprime o vetor */
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", vet[i]); /* imprime cada elemento */
    printf("\n");              /* pula uma linha */
}

typedef struct
{
    int *vet;   /* vetor com os elementos */
    int n, max; /* n = o numero de elementos e max = tamanho do vetor */
} TDicionario;  /* definindo o tipo dicionario */

TDicionario *TDicionario_Inicia() /* função que inicia o dicionario */
{
    TDicionario *D;
    D = (TDicionario *)malloc(sizeof(TDicionario)); /* aloca elemento pelo tipo definido anteriormente */
    D->n = 0;                                       /* começa com zero elementos */
    D->max = 10;                                    /* vetor inicial tem tamanho 10 */
    D->vet = (int *)malloc(sizeof(int) * (D->max)); /* aloca o vetor dinamicamente */
    return D;                                       /* retorna um elemento do tipo TDicionario */
}

int Encontra_Elemento(TDicionario *D, int Chave) /* funcao que encontra o elemento no vetor */
{
    int i;
    for (i = (D->n) - 1; i >= 0; i--) /* faz a busca de trás p frente */
        if (D->vet[i] == Chave)
            return i; /* se o elemento mora no vetor, retorna a posicao */
    return NIL;       /* caso contrario retorna NIL= -1 */
}

int Remove_Elemento(TDicionario *D, int Chave, int Pos) /* funcao que remove os elementos */
{
    int i;
    for (i = Pos; i < (D->n) - 1; i++) /* começa da posição até o penultimo elemento */
        D->vet[i] = D->vet[i + 1];     /* move todos os elementos uma posição para trás */
}

int Insere_Elemento(TDicionario *D, int Chave)
{
    if ((D->n) == (D->max)) /* verifica se é necessario aumentar o tamanho do vetor */
    {
        D->vet = (int *)realloc(D->vet, sizeof(int) * (2 * (D->max))); /* dobra o tamanho do vetor */
        D->max = 2 * D->max;                                           /* atualiza o tamanho maximo */
    }

    if ((D->n) == 0)
        D->vet[0] = Chave; /* atribuição para a primeira posicao */

    if ((D->n) > 0)
        D->vet[D->n] = Chave; /* atribuição para as demais posições */

    return 1; /* retorna 1 indicando que terminou a tarefa */
}

void Atribui(TDicionario *D) /* função responsavel por atribuir os elementos, junto com a função insere */
{
    int Chave;
    scanf("%d", &Chave); /* primeira leitura da chave a ser inserida */

    if ((D->n - 1) == (D->max) / 2) /* verifica se a memória está de acordo com as restrições*/
    {
        D->max = (D->max) / 2;
        D->vet = (int *)realloc(D->vet, sizeof(int) * (D->max)); /* atualiza o tamanho do vetor, caso necessário */
    }

    while (Chave >= 0) /* atribui os elementos */
    {
        if (Encontra_Elemento(D, Chave) == NIL && Insere_Elemento(D, Chave) == 1) /* insere os elementos */
            D->n = (D->n) + 1;                                                    /* atualiza a quantidade de elementos */
        scanf("%d", &Chave);                                                      /* faz a leitura para entrar novamente no laço */
    }
}

void Pesquisa(TDicionario *D) /* função de pesquisa (adição ou remoção) */
{
    int Chave, k;
    scanf("%d", &Chave); /* leitura da chave */

    while (Chave >= 0) /* verifica a positividade */
    {
        if (Encontra_Elemento(D, Chave) != NIL) /* verifica se esta no vetor */
        {
            if (Remove_Elemento(D, Chave, Encontra_Elemento(D, Chave)) == 1)
                ;                                                              /* remove o elemento */
            D->n = (D->n) - 1;                                                 /* atualiza a quantidade de elementos */
            if (D->n == (D->max) / 3)                                          /* verifica se tem memória inutil */
                D->vet = (int *)realloc(D->vet, sizeof(int) * ((D->max) / 2)); /* realoca o vetor */
        }
        else /* se não estiver, insere */
        {
            k = Insere_Elemento(D, Chave); /* variavel livre, utilizada apenas para inserir o elemento */
            D->n = (D->n) + 1;             /* atualiza a quantidade de elementos */
        }
        scanf("%d", &Chave); /* faz a leitura para entrar novamente no laço */
    }
}

int main()
{
    TDicionario *D;             /* dicionario */
    D = TDicionario_Inicia();   /* inicia o dicionario */
    Atribui(D);                 /* atribui os elementos */
    Pesquisa(D);                /* pesquisa (adição ou remoção) */
    ImprimeVetor(D->n, D->vet); /* imprime o vetor final */

    free(D->vet); /* libera a memoria alocada */
}
