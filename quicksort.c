//Lucas Eduardo Nogueira Gon�alves, 122055 (Integral)
#include <stdio.h>
#include <stdlib.h>

int Particao(int *vet, int p, int r) /* particiona o vetor utilizando o pivo */
{
    int aux, pivo, i, j;
    pivo = vet[r]; /* pivo � o ultimo elemento */
    i = p - 1;     /* i come�a antes do primeiro elemento */
    j = i + 1;     /* j � come�a olhando a primeira posi��o */
    while (j <= r) /* analisamos at� o pivo */
    {
        if (vet[j] <= pivo) /* se os elementos s�o menores, mant�m antes do j*/
        {
            aux = vet[i + 1]; /* troca os elementos */
            vet[i + 1] = vet[j];
            vet[j] = aux;
            j++; /* incrementa j e i (olha para proxima posi��o) */
            i++;
        }
        else /* caso contrario apenas acrescente o j */
            j++;
    }
    return (i);
}

void Imprimevetor(int n, int *vet) /* fun��o de impress�o */
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", vet[i]);
    printf("\n");
}

void QuickSort(int n, int p, int r, int *vet) /* quick recursivo */
{
    int pospivo;
    pospivo = Particao(vet, p, r); /* posic�o do pivo */

    if (p < r)
    {
        if (r != n) /* n�o temos o que imprimir neste caso */
            Imprimevetor(n, vet);
        if (pospivo - 1 >= 0) /* verificar se existe a posi��o */
            QuickSort(n, p, pospivo - 1, vet);
        if (pospivo + 1 < n) /* verificar se existe a posi��o */
            QuickSort(n, pospivo + 1, r, vet);
    }
}

int main()
{
    int i, n, *vet;

    scanf("%d", &n);                      /* leitura do tamanho do vetor */
    vet = (int *)malloc(sizeof(int) * n); /* aloca��o */
    for (i = 0; i < n; i++)
        scanf("%d", &vet[i]);    /* atribui��o */
    QuickSort(n, 0, n - 1, vet); /* chamada p o quick recursivo */

    free(vet); /* libera a memoria utilizada */
    return 0;
}
