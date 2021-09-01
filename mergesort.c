//Lucas Eduardo Nogueira Gonçalves, 122055 (Integral)
#include <stdio.h>
#include <stdlib.h>

void Imprimevetor(int n, int *vet) /* função de impressão */
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", vet[i]);
    printf("\n");
}

void Intercala(int inicio, int fim, int meio, int *vet, int *vetaux) /* intercalação (ordenação) */
{
    int i, j, k;
    if (vet[meio + 1] < vet[meio]) /* verifica se o vetor ja não esta ordenado */
    {
        for (i = inicio; i <= fim; i++)
            vetaux[i] = vet[i]; /* atribuição para o vetor auxiliar */
        j = inicio;
        k = meio + 1;
        for (i = inicio; i <= fim; i++) /* laço para atribuição do vetor auxiliar para o vetor ordenado */
            if (vetaux[k] < vetaux[j])
                if (k <= fim) /* verifica se ainda não estamos analisando a calda */
                    vet[i] = vetaux[k++];
                else /* caso contrario, não tem o que ordenar*/
                    vet[i] = vetaux[j++];
            else if (j <= meio) /* verifica se ainda podemos atribuir após a cabeça e antes do meio */
                vet[i] = vetaux[j++];
            else /* caso contrario, não tem o que ordenar*/
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
        Imprimevetor(n, vet);                      /* imprime após ordenação */
    }
}

int main()
{
    int n, i, *vet, *vetaux;
    scanf("%d", &n);                         /* leitura do tamanho do vetor*/
    vet = (int *)malloc(sizeof(int) * n);    /* alocação */
    vetaux = (int *)malloc(sizeof(int) * n); /* alocação do vetor auxiliar */
    for (i = 0; i < n; i++)
        scanf("%d", &vet[i]);            /* leitura dos elementos */
    MergeSort(n, 0, n - 1, vet, vetaux); /* chamada recursiva para separação e ordenação */

    free(vet);    /* libera memória */
    free(vetaux); /* libera memória */
    return 0;
}
