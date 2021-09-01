//Lucas Eduardo Nogueira Gonçalves, 122055 (Integral)
#include <stdio.h>
#include <stdlib.h>

typedef struct SNo *TArv;

typedef struct SNo
{
    int Chave;     /* Chave do tipo inteiro */
    TArv Esq, Dir; /* Caminhos, direita ou esquerda */
    int FB;        /* Fator de Balanceamento */
} TNo;

typedef struct Arvore /* Arvore de Busca Binária */
{
    TArv Raiz; /* Raiz da Arvore (primeiro elemento) */
} TABB;

int Altura(TArv No) /* Função que retorna a altura de um determinado Nó */
{
    if (No == NULL)
        return -1; /* Se não possui, a altura é -1 (pode se considerar como uma arvore sem nenhum elemento) */

    if (Altura(No->Esq) > Altura(No->Dir)) /* Verifica qual dos "ramos" é o maior */
        return (Altura(No->Esq) + 1);      /* Retorna o maior somado com a raiz */
    return (Altura(No->Dir) + 1);          /* Retorna o maior somado com a raiz */
}

int FatorBalanceamento(TArv No) /* Retorna e edita o fator de balanceamento de um nó */
{
    if (No != NULL)
        No->FB = Altura(No->Esq) - Altura(No->Dir); /* Se for não nulo, faz a diferença entre as alturas */
    return (No->FB);                                /* Retorna o fator */
}

TArv Menor(TArv No) /* Procura o menor elemento à direita */
{
    TArv N1, N2;
    N1 = No;
    N2 = No->Dir;      /* Anda um para a direita */
    while (N2 != NULL) /* Procura o menor elemento, desce a esquerda da direita */
    {
        N1 = N2;
        N2 = N2->Esq;
    }
    return N1; /* Retorna o Nó com o menor elemento */
}

TArv Pesquisa(TArv No, int Chave) /* Pesquisa uma determinada chave */
{
    if (No == NULL)
        return NULL; /* Se chegou até o fim e não encontrou, retorna NULL */

    if (No->Chave == Chave)
        return No; /* Se encontrou o elemento, retorna o Nó*/

    if (Chave < No->Chave) /* Se a chave a ser pesquisada for menor, analisa os elementos da esquerda */
        return Pesquisa(No->Esq, Chave);
    return Pesquisa(No->Dir, Chave); /* Se a chave a ser pesquisada for maioor, analisa os elementos da direita */
}

void Rot_RR(TArv *Raiz) /* Rotação RightRight */
{
    TArv pA, pB;
    pA = (*Raiz); /* Atribuições */
    pB = (*Raiz)->Esq;

    pA->Esq = pB->Dir; /* Rotação */
    pB->Dir = pA;

    (*Raiz) = pB; /* A raiz recebe o pB e terminamos a rotação */

    pA->FB = Altura(pA->Esq) - Altura(pA->Dir); /* Atualiza os fatores de balanceamento */
    pB->FB = Altura(pB->Esq) - Altura(pB->Dir); /* Atualiza os fatores de balanceamento */
}

void Rot_RL(TArv *Raiz) /* Rotação RightLeft */
{
    TArv pA, pB, pC;
    pA = (*Raiz); /* Atribuições */
    pB = (*Raiz)->Esq;
    pC = (*Raiz)->Esq->Dir;

    pA->Esq = pC->Dir; /* Rotação */
    pB->Dir = pC->Esq;
    pC->Dir = pA;
    pC->Esq = pB;

    (*Raiz) = pC; /* A raiz recebe o pC e terminamos a rotação */

    pA->FB = Altura(pA->Esq) - Altura(pA->Dir); /* Atualiza os fatores de balanceamento */
    pB->FB = Altura(pB->Esq) - Altura(pB->Dir); /* Atualiza os fatores de balanceamento */
    pC->FB = Altura(pC->Esq) - Altura(pC->Dir); /* Atualiza os fatores de balanceamento */
}

void Rot_LL(TArv *Raiz)
{
    TArv pA, pB;
    pA = (*Raiz); /* Atribuições */
    pB = (*Raiz)->Dir;

    pA->Dir = pB->Esq; /* Rotação */
    pB->Esq = pA;

    (*Raiz) = pB; /* A raiz recebe o pC e terminamos a rotação */

    pA->FB = Altura(pA->Esq) - Altura(pA->Dir); /* Atualiza os fatores de balanceamento */
    pB->FB = Altura(pB->Esq) - Altura(pB->Dir); /* Atualiza os fatores de balanceamento */
}

void Rot_LR(TArv *Raiz)
{
    TArv pA, pB, pC;
    pA = (*Raiz); /* Atribuições */
    pB = (*Raiz)->Dir;
    pC = (*Raiz)->Dir->Esq;

    pA->Dir = pC->Esq; /* Rotação */
    pB->Esq = pC->Dir;
    pC->Esq = pA;
    pC->Dir = pB;

    (*Raiz) = pC; /* A raiz recebe o pC e terminamos a rotação */

    pA->FB = Altura(pA->Esq) - Altura(pA->Dir); /* Atualiza os fatores de balanceamento */
    pB->FB = Altura(pB->Esq) - Altura(pB->Dir); /* Atualiza os fatores de balanceamento */
    pC->FB = Altura(pC->Esq) - Altura(pC->Dir); /* Atualiza os fatores de balanceamento */
}

void VerificaRot(TArv *Raiz) /* Verifica se é necessário a rotação */
{
    if (*Raiz != NULL) /* Se for não nula, analisamos os casos */
    {
        FatorBalanceamento((*Raiz)); /* Atualizamos os fatores de balanceamento */
        if (!(-2 < (*Raiz)->FB) || !((*Raiz)->FB < 2))
        {
            if ((*Raiz)->FB == 2) /* Temos que a maior (sub)arvore se encontra na esquerda */
            {
                if ((*Raiz)->Esq->FB == -1)      /* Se a diferença for um, rotação simples */
                    Rot_RL(Raiz);                /* Faz Rotação RightLeft */
                else if ((*Raiz)->Esq->FB != -1) /* Se a diferença for maior que um, rotação dupla */
                    Rot_RR(Raiz);                /* Faz Rotação RightRight */
            }
            else if ((*Raiz)->FB == -2) /* Temos que a maior (sub)arvore se encontra na direita */
            {
                if ((*Raiz)->Dir->FB == 1)      /* Se a diferença for um, rotação simples */
                    Rot_LR(Raiz);               /* Faz Rotação LeftRight */
                else if ((*Raiz)->Dir->FB != 1) /* Se a diferença for maior que um, rotação dupla */
                    Rot_LL(Raiz);               /* Faz Rotação LeftLeft */
            }
        }
    }
}

int Remove(TArv *No, int Chave) /* Função responsável por remover o Nó */
{
    TArv NovoNo;       /* Novo nó, auxiliar */
    if ((*No) == NULL) /* Se a raiz (ou nó) for nulo, não temos mais como remover */
        return 0;

    if ((*No)->Chave == Chave) /* Se encontramos o que desejamos remover temos algumas condições */
    {
        if ((*No)->Esq == NULL && (*No)->Dir == NULL) /* Não possui filho a direita nem a esquerda (folha) */
        {
            free((*No));  /* Libera a memória utilizada */
            (*No) = NULL; /* Aponta para NULL */
        }
        else if ((*No)->Esq != NULL && (*No)->Dir != NULL) /* Se o Nó possui dois filhos */
        {
            NovoNo = Menor(*No);          /* Novo Nó recebe o Nó com o menor elemento a direita */
            (*No)->Chave = NovoNo->Chave; /* Atualizamos a Raiz */

            if (Remove(&(*No)->Dir, NovoNo->Chave) == 0) /* Se falhou, retorna zero */
                return 0;
        }
        else /* Caimos no caso que temos apenas um filho */
        {
            if ((*No)->Esq == NULL) /* Se a esquerda não tiver ninguém */
                NovoNo = (*No)->Dir;
            else /* Se a direita não tiver ninguém */
                NovoNo = (*No)->Esq;

            free((*No)); /* Libera memória */

            (*No) = NovoNo; /* Atualiza o Nó */
        }
    }
    else
    {
        if ((*No)->Chave < Chave) /* Se a chave a ser inserida é maior */
        {
            if (Remove(&((*No)->Dir), Chave)) /* Se a remoção acontecer */
            {
                (*No)->FB = (*No)->FB + 1; /* Atualizamos os fatores de balanceamento */

                if ((*No)->FB == 1) /* Aceitamos apenas 1 ou zero */
                    return 1;       /* Temos as condições necessárias e suficientes para retornar que deu certo */
                else if ((*No)->FB == 0)
                    return 0; /* Não podemos retornar que deu certo */
            }
        }

        else if ((*No)->Chave > Chave) /* Caso contrário a ser inserida é menor */
        {
            if (Remove(&((*No)->Esq), Chave)) /* Se a remoção acontecer */
            {
                (*No)->FB = (*No)->FB - 1; /* Atualizamos os fatores de balanceamento */

                if ((*No)->FB == -1) /* Aceitamos apenas -1 ou zero, estamos a esquerda */
                    return 1;        /* Temos as condições necessárias e suficientes para retornar que deu certo */
                else if ((*No)->FB == 0)
                    return 0; /* Não podemos retornar que deu certp */
            }
        }
        VerificaRot(No); /* Verifica se é necessário uma rotação */
    }
    return 1; /* Após a rotação, está tudo certo. */
}

int Insere(TArv *No, int Chave) /* Função responsável por inserir o Nó*/
{
    if (*No == NULL) /* Encontramos onde o elemento deve ser inserido */
    {
        TArv NovoNo = (TNo *)malloc(sizeof(TNo));
        NovoNo->FB = 0;
        NovoNo->Chave = Chave;
        NovoNo->Esq = NULL;
        NovoNo->Dir = NULL;
        (*No) = NovoNo; /* Inserimos o novo elemento */
        return 1;
    }

    if ((*No)->Chave == Chave) /* Se o elemento já existir na arvore, não inserimos */
        return 0;

    if (Chave < (*No)->Chave) /* Procurando o elemento, caso que a chave é menor que a chave do nó */
    {
        if (Insere(&((*No)->Esq), Chave)) /* Se for ocorrer tudo certo, atualizamos o fator de balanceamento */
        {
            (*No)->FB = (*No)->FB + 1; /* Atualizamos o fator de balanceamento */

            if ((*No)->FB == 0)
                return 0;
            else if ((*No)->FB == 1) /* Temos as condições necessárias e suficientes para retornar que deu certo */
                return 1;
            else
                VerificaRot(No); /* Verifica se é necessário uma rotação */
        }
    }
    else /* Procurando o elemento, caso que a chave é maior que a chave do nó */
    {
        if (Insere(&(*No)->Dir, Chave))
        {
            (*No)->FB = (*No)->FB - 1; /* Atualizamos o fator de balanceamento */

            if ((*No)->FB == 0)
                return 0;
            else if ((*No)->FB == -1) /* Temos as condições necessárias e suficientes para retornar que deu certo */
                return 1;
            else
                VerificaRot(No); /* Verifica se é necessário uma rotação */
        }
    }
    VerificaRot(No); /* Verifica se é necessário uma rotação */
    return 1;        /* Ocorreu tudo certo */
}

void ImprimePreOrdem(TNo *A) /* Função responsável por imprimir em pré-ordem */
{
    if (A != NULL)
    {
        printf("%d ", A->Chave); /* Raiz */
        ImprimePreOrdem(A->Esq); /* Esquerda */
        ImprimePreOrdem(A->Dir); /* Direita */
    }
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

TABB *Inicializa() /* Função responsável por incializar a arvore */
{
    TABB *A = (TABB *)malloc(sizeof(TABB));
    A->Raiz = NULL; /* Raiz recebe NULL */
    return A;       /* Retornamos a arvore */
}

void Atribui(TABB *Arvore) /* Função de atribuição, utilizada para chamar o insere até a presença de um número negativo */
{
    int Chave;
    scanf("%d", &Chave);
    while (Chave >= 0)
    {
        Insere(&(Arvore->Raiz), Chave);
        scanf("%d", &Chave);
    }
}

void PesqRemovIn(TABB *Arvore) /* Função de pesquisa e remoção, utilizada para pesquisar e analisar se é necessario inserir ou remover */
{
    int Chave;
    scanf("%d", &Chave);

    while (Chave >= 0)
    {
        Remove(&(Arvore->Raiz), Chave);
        scanf("%d", &Chave);
    }
}

int main() /* Função principal */
{
    TABB *Arvore = Inicializa(); /* Inicializa Arvore */

    Atribui(Arvore); /* Atribui os elementos */

    ImprimePreOrdem(Arvore->Raiz); /* Imprime em pré ordem */
    printf("\n");
    printf("%d", Altura(Arvore->Raiz)); /* Imprime a altura */
    printf("\n");

    PesqRemovIn(Arvore); /* Pesquisa e Remove(ou Insere) */

    ImprimePreOrdem(Arvore->Raiz); /* Imprime em pré ordem */
    printf("\n");
    printf("%d", Altura(Arvore->Raiz)); /* Imprime a altura */
    printf("\n");

    Libera(Arvore->Raiz); /* Libera a memória */

    return 0;
}
