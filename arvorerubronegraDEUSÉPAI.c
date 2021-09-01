//Lucas Eduardo Nogueira Gonçalves, 122055 (Integral)
#include <stdio.h>
#include <stdlib.h>

typedef struct SNo *TArv;

typedef struct SNo
{
    int Chave;     /* Chave do tipo inteiro */
    TArv Esq, Dir; /* Caminhos, direita ou esquerda */
    int Cor;       /*1 - rubro e 0 - negro */
} TNo;

typedef struct Arvore /* Arvore de Busca Binária */
{
    TArv Raiz; /* Raiz da Arvore (primeiro elemento) */
} TABB;

TABB *Inicializa() /* Função responsável por incializar a arvore */
{
    TABB *A = (TABB *)malloc(sizeof(TABB));
    A->Raiz = NULL; /* Raiz recebe NULL */
    return A;       /* Retornamos a arvore */
}

void TrocaCores(TArv No) /* Inverte a cor de um nó */
{
    if ((No) != NULL)           /* Verifica se o Nó é nulo */
        (No)->Cor = !(No)->Cor; /* Se era rubro vira negro, se era negro vira rubro */
}

void Imprime(TArv No) /* Função responsável por imprimir */
{
    char c;
    printf("(");
    if (No != NULL) /* Verificamos se o nó é não nulo */
    {
        if (No->Cor == 0)
            c = 'N';
        else
            c = 'R';

        printf("%c%d", c, No->Chave); /* Imprime a cor */
        Imprime(No->Esq);             /* Esquerda */
        Imprime(No->Dir);             /* Direita */
    }
    printf(")");
}

void Libera(TNo *No) /* Liberamos todo o espaço utilizamos após o fim do programa */
{
    if (No != NULL)
    {
        Libera(No->Dir); /* Libera cada nó */
        Libera(No->Esq);
        free(No); /* Libera a memória */
    }
}

int AlturaNegra(TArv No) /* Retorna a altura negra de um determinado no */
{
    if (No == NULL) /* Se o Nó for nulo, não temos o que olhar */
        return 0;
    else /* Caso contrário vamos percorrer os dois possiveis caminhos e procurar o maior */
    {
        if (AlturaNegra(No->Esq) > AlturaNegra(No->Dir)) /* Se a esquerda for maior que a direita procuramos onde esta a diferença */
        {
            if (No->Cor == 0)
                return AlturaNegra(No->Esq) + 1; /* Incrementa na altura */
            else
                return AlturaNegra(No->Esq);
        }
        else /* Caso analogo ao anterior */
        {
            if (No->Cor == 0)
                return AlturaNegra(No->Dir) + 1; /* Incrementa na altura */
            else
                return AlturaNegra(No->Dir);
        }
    }
}

int ArvoreARN(TArv No) /* Retorna 1 se a (sub) arvore for rubro negra */
{
    if (No == NULL)
        return 1;                                      /* Um Nó nulo por vacuidade é sempre uma arvore rubro negra */
    else if (ArvoreARN(No->Esq) && ArvoreARN(No->Dir)) /* Se ambas subarvores forem, olhamos os casos */
    {
        int vef = 0;
        if (AlturaNegra(No->Esq) == AlturaNegra(No->Dir)) /* As alturas coincidem */
        {
            if (No->Cor == 0) /* A (sub)Raiz é Negra */
                return 1;
            else
            {
                if (No->Esq == NULL && No->Dir == NULL) /* Ambos os filhos são nulos (temos que o nó é rubro) */
                    return 1;
                else
                {
                    if (No->Esq != NULL && No->Esq->Cor == 1)
                        vef++;
                    if (No->Dir != NULL && No->Dir->Cor == 1)
                        vef++;
                }
                if (vef == 0) /* Não temos pai e filho rubro */
                    return 1;
                else /* Caso de falha */
                    return 0;
            }
        }
        else /* A Raiz é Negra */
            return 0;
    }
    else /* A Raiz é Negra */
        return 0;
}

void RotacaoDireita(TArv *pA) /* Faz a rotação simples para a direita */
{
    TArv pB;

    pB = (*pA)->Esq; /* Define quem vai participar da troca */

    if (pB != NULL)
    {
        (*pA)->Esq = pB->Dir; /* Atribuições */
        pB->Dir = (*pA);
    }
    (*pA) = pB; /* Troca pA com pB */
}

void RotacaoEsquerda(TArv *pA) /* Faz a rotação simples para a esquerda */
{
    TArv pB;

    pB = (*pA)->Dir; /* Define quem vai participar da troca */
    if (pB != NULL)
    {
        (*pA)->Dir = pB->Esq; /* Atribuições */
        pB->Esq = (*pA);
    }
    (*pA) = pB; /* Troca pA com pB */
}

void BalancaNo(TArv *Avo, TArv *Pai, TArv *Filho) /* Função responsavel por balancear o Nó */
{
    TArv Tio = NULL; /* Cria um nó nulo */

    if (*Pai != NULL && *Filho != NULL)             /* Verificamos se o pai e o filho são não, caso sim, verificamos os casos */
        if ((*Pai)->Cor == 1 && (*Filho)->Cor == 1) /* Pai e Filho são Rubros */
        {
            if (Avo != NULL) /* Se o avô for não nulo */
            {
                if ((*Avo)->Esq == (*Pai)) /* Verificamos quem é o pai */
                    Tio = (*Avo)->Dir;
                else /* Definimos quem é o tio */
                    Tio = (*Avo)->Esq;
            }

            if ((Tio != NULL) && (Tio->Cor == 1)) /* Tio é Rubro */
            {
                if (Avo != NULL) /* Se o avô for não nulo */
                {
                    TrocaCores(*Pai);
                    TrocaCores(Tio); /* Todos trocam de Cor */
                    TrocaCores(*Avo);
                }
            }

            else /* Se o tio for nulo ou negro */
            {
                if (Avo != NULL) /* Se o avo for não nulo */
                {
                    if ((*Avo)->Dir == (*Pai)) /* Verificamos em que lado do avo está o pai */
                    {
                        if ((*Pai)->Esq == (*Filho)) /* Pai e filho em lados diferentes */
                            RotacaoDireita(Pai);
                        TrocaCores(*Avo); /* Troca cor e rotaciona */
                        TrocaCores(*Pai);
                        RotacaoEsquerda(Avo);
                    }

                    else /* Esta do outro lado */
                    {
                        if ((*Pai)->Dir == (*Filho)) /* Pai e filho do mesmo lado */
                            RotacaoEsquerda(Pai);    /* Rotaciona o Pai */
                        TrocaCores(*Avo);
                        TrocaCores(*Pai); /* Troca cor e rotaciona */
                        RotacaoDireita(Avo);
                    }
                }
            }
        }
}

int Insere(TArv *Raiz, TArv *Pai, TArv *Avo, int Chave) /* Função responsavel por inserir */
{
    if (*Pai == NULL) /* Encontramos onde o elemento deve ser inserido */
    {
        TArv NovoNo = (TNo *)malloc(sizeof(TNo));
        NovoNo->Cor = 1;
        NovoNo->Chave = Chave;
        NovoNo->Esq = NULL;
        NovoNo->Dir = NULL;
        (*Pai) = NovoNo;
        return 1;
    }

    if ((*Pai)->Chave == Chave) /* Se o elemento já existir na arvore, não inserimos */
        return 0;

    else /* Outros casos */
    {
        if (Chave < (*Pai)->Chave) /* A chave é menor */
        {
            if (Insere(Raiz, &(*Pai)->Esq, Pai, Chave)) /* Insere o elemento */
                if (ArvoreARN(*Raiz) == 0)              /* Verifica se é necessario balancear */
                    BalancaNo(Avo, Pai, &(*Pai)->Esq);  /* Ocorre o balanceamento */
        }

        else /* A chave é maior */
        {
            if (Insere(Raiz, &(*Pai)->Dir, Pai, Chave)) /* Insere o elemento */
                if (ArvoreARN(*Raiz) == 0)              /* Verifica se é necessario balancear */
                    BalancaNo(Avo, Pai, &(*Pai)->Dir);  /* Ocorre o balanceamento */
        }
    }

    if ((*Raiz) != NULL)  /* Verificamos se a raiz é não nula */
        (*Raiz)->Cor = 0; /* Mudamos a cor da raiz */

    return 1;
}

void Atribui(TABB *Arvore) /* Função de atribuição, utilizada para chamar o insere*/
{
    int Chave, n, i;

    scanf("%d", &n); /* Leitura da quantidade de elementos a ser inseridos */

    if (n > 0)
        for (i = 0; i < n; i++)
        {
            scanf("%d", &Chave);
            Insere(&(Arvore->Raiz), &(Arvore->Raiz), NULL, Chave); /* Insere elemento */
        }
}

int main()
{
    TABB *Arvore = Inicializa(); /* Inicializa Arvore */
    Atribui(Arvore);             /* Atribui os elementos */

    printf("%d\n", AlturaNegra(Arvore->Raiz)); /* Imprime a altura negra */
                                               /* Como a arvore sempre será rubro negra, imprimimos a arvore */
    Imprime(Arvore->Raiz);

    Libera(Arvore->Raiz); /* Libera memória alocada */

    return 0;
}
