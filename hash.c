//Lucas Eduardo Nogueira Gonçalves, 122055 (Integral)

#include <stdio.h>
#include <stdlib.h>

typedef struct SCelula *tApontador; /* Apontador */

typedef struct SCelula
{
    int Chave;            /* Tipo da Chave */
    tApontador Prox, Ant; /* Ponteiro para o próximo e o anterior */
} TCelula;

typedef struct
{
    int Tam;           /* Tamanho da Lista */
    tApontador Inicio; /* Cabeça da Lista */
} TLista;

void Imprime_Hash(TLista *Tabela[], int m) /* Função responsável por imprimir a lista */
{
    int i;          /* Contador */
    tApontador aux; /* Auxiliar */

    for (i = 0; i < m; i++)
    {
        aux = (Tabela[i])->Inicio->Prox;
        printf("[%d] ", i); /* Imprime a Tabela */

        while (aux != (Tabela[i])->Inicio)
        {
            printf("%d ", aux->Chave); /* Imprime o elemento na Tabela */
            aux = aux->Prox;
        }
        printf("\n");
    }
}

TLista *ListaInicia() /* Função responsável por inciar a lista */
{
    TLista *Lista;
    Lista = (TLista *)malloc(sizeof(TLista));            /* Aloca a memória */
    Lista->Tam = 0;                                      /* Inicia o tamanho com zero */
    Lista->Inicio = (tApontador)malloc(sizeof(TCelula)); /* Aloca o elemento do inicio */
    Lista->Inicio->Prox = Lista->Inicio;                 /* Aponta para o inicio */
    Lista->Inicio->Ant = Lista->Inicio;                  /* Aponta para o inicio*/

    return Lista;
}

int Insere_Hash(TLista *Lista, int a) /* Função responsavel por inserir */
{

    tApontador Novo;                            /* Cria um novo apontador */
    Novo = (tApontador)malloc(sizeof(TCelula)); /* Aloca memória */
    Novo->Chave = a;                            /* Recebe a chave */

    if (Lista->Tam == 0) /* Se a lista não tiver nenhum elemento */
    {
        Lista->Inicio->Prox = Novo; /* Coloca na primeira posição */
        Novo->Ant = Lista->Inicio;
        Novo->Prox = Lista->Inicio;
        Lista->Inicio->Ant = Novo;
        Lista->Inicio->Prox = Novo;
        Lista->Tam++;
        return 1;
    }

    else /* Caso contrario */
    {
        Novo->Prox = Lista->Inicio;
        Novo->Ant = Lista->Inicio->Ant;
        Lista->Inicio->Ant->Prox = Novo; /* Coloca na última posição */
        Lista->Inicio->Ant = Novo;
        Lista->Tam++;
        return 1;
    }
}

tApontador Pesquisa_Hash(TLista *Lista, int a) /* Função responsável por pesquisar */
{
    tApontador aux = Lista->Inicio->Prox; /* Auxiliar */

    while (aux->Chave != a && aux != Lista->Inicio)
        aux = aux->Prox;

    if (aux == Lista->Inicio)
        return NULL; /* Pesquisa sem sucesso */

    return aux; /* Pesquisa c sucesso */
}

int Remove_Hash(TLista *Lista, int a) /* Função responsavel por remover */
{
    tApontador aux = Pesquisa_Hash(&(*Lista), a); /* Auxiliar */

    aux->Ant->Prox = aux->Prox;
    aux->Prox->Ant = aux->Ant;
    free(aux);    /* Libera a memoria */
    Lista->Tam--; /* Diminui o tamanho da lista */
}

int main()
{
    int i, m, n, Chave;

    scanf("%d", &m); /* mod m */
    scanf("%d", &n); /* Quantidade de elementos */
    TLista *Tabela[m];

    for (i = 0; i < m; i++) /* Inicia m listas */
        Tabela[i] = ListaInicia();

    for (i = 0; i < n; i++)
    {
        scanf("%d", &Chave);                       /* Leitura dos elementos */
        Insere_Hash(&(*Tabela[Chave % m]), Chave); /* Inserção */
    }

    scanf("%d", &Chave);

    if (Pesquisa_Hash(&(*Tabela[Chave % m]), Chave) == NULL) /* Se não esta, insere */
        Insere_Hash(&(*Tabela[Chave % m]), Chave);
    else
        Remove_Hash(&(*Tabela[Chave % m]), Chave); /* cc remove */

    Imprime_Hash(Tabela, m); /* Imprime a tabela Hash */
}
