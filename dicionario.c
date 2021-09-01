//Lucas Eduardo Nogueira Gon�alves, 122055 (Integral)
#include <stdio.h>
#include <stdlib.h>
#define NIL -1

void ImprimeVetor(int n, int *vet) /* fun��o que imprime o vetor */
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

TDicionario *TDicionario_Inicia() /* fun��o que inicia o dicionario */
{
    TDicionario *D;
    D = (TDicionario *)malloc(sizeof(TDicionario)); /* aloca elemento pelo tipo definido anteriormente */
    D->n = 0;                                       /* come�a com zero elementos */
    D->max = 10;                                    /* vetor inicial tem tamanho 10 */
    D->vet = (int *)malloc(sizeof(int) * (D->max)); /* aloca o vetor dinamicamente */
    return D;                                       /* retorna um elemento do tipo TDicionario */
}

int Encontra_Elemento(TDicionario *D, int Chave) /* funcao que encontra o elemento no vetor */
{
    int i;
    for (i = (D->n) - 1; i >= 0; i--) /* faz a busca de tr�s p frente */
        if (D->vet[i] == Chave)
            return i; /* se o elemento mora no vetor, retorna a posicao */
    return NIL;       /* caso contrario retorna NIL= -1 */
}

int Remove_Elemento(TDicionario *D, int Chave, int Pos) /* funcao que remove os elementos */
{
    int i;
    for (i = Pos; i < (D->n) - 1; i++) /* come�a da posi��o at� o penultimo elemento */
        D->vet[i] = D->vet[i + 1];     /* move todos os elementos uma posi��o para tr�s */
}

int Insere_Elemento(TDicionario *D, int Chave)
{
    if ((D->n) == (D->max)) /* verifica se � necessario aumentar o tamanho do vetor */
    {
        D->vet = (int *)realloc(D->vet, sizeof(int) * (2 * (D->max))); /* dobra o tamanho do vetor */
        D->max = 2 * D->max;                                           /* atualiza o tamanho maximo */
    }

    if ((D->n) == 0)
        D->vet[0] = Chave; /* atribui��o para a primeira posicao */

    if ((D->n) > 0)
        D->vet[D->n] = Chave; /* atribui��o para as demais posi��es */

    return 1; /* retorna 1 indicando que terminou a tarefa */
}

void Atribui(TDicionario *D) /* fun��o responsavel por atribuir os elementos, junto com a fun��o insere */
{
    int Chave;
    scanf("%d", &Chave); /* primeira leitura da chave a ser inserida */

    if ((D->n - 1) == (D->max) / 2) /* verifica se a mem�ria est� de acordo com as restri��es*/
    {
        D->max = (D->max) / 2;
        D->vet = (int *)realloc(D->vet, sizeof(int) * (D->max)); /* atualiza o tamanho do vetor, caso necess�rio */
    }

    while (Chave >= 0) /* atribui os elementos */
    {
        if (Encontra_Elemento(D, Chave) == NIL && Insere_Elemento(D, Chave) == 1) /* insere os elementos */
            D->n = (D->n) + 1;                                                    /* atualiza a quantidade de elementos */
        scanf("%d", &Chave);                                                      /* faz a leitura para entrar novamente no la�o */
    }
}

void Pesquisa(TDicionario *D) /* fun��o de pesquisa (adi��o ou remo��o) */
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
            if (D->n == (D->max) / 3)                                          /* verifica se tem mem�ria inutil */
                D->vet = (int *)realloc(D->vet, sizeof(int) * ((D->max) / 2)); /* realoca o vetor */
        }
        else /* se n�o estiver, insere */
        {
            k = Insere_Elemento(D, Chave); /* variavel livre, utilizada apenas para inserir o elemento */
            D->n = (D->n) + 1;             /* atualiza a quantidade de elementos */
        }
        scanf("%d", &Chave); /* faz a leitura para entrar novamente no la�o */
    }
}

int main()
{
    TDicionario *D;             /* dicionario */
    D = TDicionario_Inicia();   /* inicia o dicionario */
    Atribui(D);                 /* atribui os elementos */
    Pesquisa(D);                /* pesquisa (adi��o ou remo��o) */
    ImprimeVetor(D->n, D->vet); /* imprime o vetor final */

    free(D->vet); /* libera a memoria alocada */
}
