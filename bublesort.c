//Lucas Eduardo Nogueira Gonçalves, 122055 (Integral)
#include <stdio.h>
#include <stdlib.h>

void Imprimebalde(int n, float vet[]) /* função utilizada para imprimir cada balde */
{
    int i;
    for (i = 0; i < n; i++)
        printf("%7.3f", vet[i]); /* vetor de float */
    printf("\n");                /* pula uma linha */
}

void Imprimebaldenovo(int n, float vet[]) /* função utilizada para imprimir todos os numeros */
{
    int i;
    for (i = 0; i < n; i++)
        printf("%7.3f", vet[i]); /* vetor de float */
}

void BubleSort(int n, float vet[]) /* BubleSort */
{
    int i, j;
    float aux;
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++) /* note que j varia até n-i-1, o maior elemento sempre está no final */
            if (vet[j] > vet[j + 1])    /* se for maior, faço a troca */
            {
                aux = vet[j];
                vet[j] = vet[j + 1];
                vet[j + 1] = aux;
            }
}

void BucketSort(int n, int b, float *vet) /* BucketSort */
{
    int i, m, vetind[b]; /* vetor de dimensão b, ele guarda o indice dos baldes */
    float balde[b][n];   /* matriz bxn, a primeira entrada representa o balde e a outra o vetor que guarda os elementos do balde */
    for (i = 0; i < b; i++)
        vetind[i] = 0; /* inicio o indice de cada balde como zero*/

    for (i = 0; i < n; i++)
        if ((vet[i] * b) < b) /* se o produto for menor que a quantidade de baldes */
        {
            m = (int)(vet[i] * b);        /* parte inteira da multiplicação */
            balde[m][vetind[m]] = vet[i]; /* coloco o elmento na matriz */
            vetind[m]++;                  /* incremento o indice */
        }
        else /* caso contrário ele é maior e colocamos no ultimo balde*/
        {
            balde[b - 1][vetind[b - 1]] = vet[i];
            vetind[b - 1]++;
        }

    for (i = 0; i < b; i++)
        if (vetind[i] != 0) /* se o indice for diferente de zero, imprime o conteudo do balde*/
        {
            printf("%d-> ", i);                /* número do balde */
            Imprimebalde(vetind[i], balde[i]); /* imprime os elementos*/
        }
    printf("\n");

    for (i = 0; i < b; i++)
        BubleSort(vetind[i], balde[i]); /* ordena cada balde */

    for (i = 0; i < b; i++)
        if (vetind[i] != 0) /* se o indice for diferente de zero, imprime o conteudo do balde*/
        {
            printf("%d-> ", i);                /* número do balde */
            Imprimebalde(vetind[i], balde[i]); /* imprime os elementos*/
        }
    printf("\n");

    for (i = 0; i < b; i++)
        Imprimebaldenovo(vetind[i], balde[i]); /* imprime todos os elementos do balde */
}

int main()
{
    int i, n, b;
    float *vet;                               /* vetor de float */
    scanf("%d", &n);                          /* tamanho do vetor*/
    scanf("%d", &b);                          /* quantidade de baldes */
    vet = (float *)malloc(sizeof(float) * n); /* aloca o vetor */
    for (i = 0; i < n; i++)
        scanf("%f", &vet[i]); /* leitura dos elementos */
    BucketSort(n, b, vet);    /* ordena */

    free(vet); /* libera memoria */
}
