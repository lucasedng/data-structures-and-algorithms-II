//Lucas Eduardo Nogueira Gon�alves, 122055 (Integral)
#include <stdio.h>
#include <stdlib.h>

void Imprimevetor(int n, int *vet) /* fun��o de impress�o */
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", vet[i]);
    printf("\n");
}

void Intercala(int inicio, int fim, int meio, int *vet, int *vetaux) /* intercala��o (ordena��o) */
{
    int i, j, k;
    if (vet[meio + 1] < vet[meio]) /* verifica se o vetor ja n�o esta ordenado */
    {
        for (i = inicio; i <= fim; i++)
            vetaux[i] = vet[i]; /* atribui��o para o vetor auxiliar */
        j = inicio;
        k = meio + 1;
        for (i = inicio; i <= fim; i++) /* la�o para atribui��o do vetor auxiliar para o vetor ordenado */
            if (vetaux[k] < vetaux[j])
                if (k <= fim) /* verifica se ainda n�o estamos analisando a calda */
                    vet[i] = vetaux[k++];
                else /* caso contrario, n�o tem o que ordenar*/
                    vet[i] = vetaux[j++];
            else if (j <= meio) /* verifica se ainda podemos atribuir ap�s a cabe�a e antes do meio */
                vet[i] = vetaux[j++];
            else /* caso contrario, n�o tem o que ordenar*/
                vet[i] = vetaux[k++];
    }
}

void MergeSort(int n, int inicio, int fim, int *vet, int *vetaux) /* Merge Recursivo */
{
    int meio = (inicio + fim) / 2; /* definimos onde vamos separar o vetor */
    if (inicio != fim)
    {
        MergeSort(n, inicio, meio, vet, vetaux);   /* separa lado esquerdo */
        MergeSort(n, meio + 1, fim, vet, vetaux);  /* separa lado direito */
        Intercala(inicio, fim, meio, vet, vetaux); /* intercala ambos os lados */
        Imprimevetor(n, vet);                      /* imprime ap�s ordena��o */
    }
}

int main()
{
    int n, i, *vet, *vetaux;
    scanf("%d", &n);                         /* leitura do tamanho do vetor*/
    vet = (int *)malloc(sizeof(int) * n);    /* aloca��o */
    vetaux = (int *)malloc(sizeof(int) * n); /* aloca��o do vetor auxiliar */
    for (i = 0; i < n; i++)
        scanf("%d", &vet[i]);            /* leitura dos elementos */
    MergeSort(n, 0, n - 1, vet, vetaux); /* chamada recursiva para separa��o e ordena��o */

    free(vet);    /* libera mem�ria */
    free(vetaux); /* libera mem�ria */
    return 0;
}
