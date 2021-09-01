//Lucas Eduardo Nogueira Gonçalves, 122055 (Integral)

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void Refaz(int n, int *vet, int j) /* refaz o heap */
{
    int aux;
    if (2 * j + 2 < n)
    {
        if (!(vet[j] > vet[2 * j + 1] && vet[j] > vet[2 * j + 2])) /* verifica se o pai é menor que algum dos filhos */
        {
            if (vet[2 * j + 1] > vet[2 * j + 2]) /* primeira opção */
            {
                /* faz a troca */
                aux = vet[j];
                vet[j] = vet[2 * j + 1];
                vet[2 * j + 1] = aux;
                Refaz(n, vet, 2 * j + 1); /* método refaz recursivo */
            }
            else /* ocorre pelo menos um das opções */
            {
                /* faz a troca */
                aux = vet[j];
                vet[j] = vet[2 * j + 2];
                vet[2 * j + 2] = aux;
                Refaz(n, vet, 2 * j + 2); /* método refaz recursivo */
            }
        }
    }
    else if (2 * j + 1 < n) /* possui apenas um filho */
    {
        if (!(vet[j] > vet[2 * j + 1])) /* note que se o pai tem apenas um filho não é preciso chamar o refaz */
        {
            /* faz a troca */
            aux = vet[j];
            vet[j] = vet[2 * j + 1];
            vet[2 * j + 1] = aux;
        }
    }
}

void Constroi(int n, int *vet) /* constroi o heap utilizando o refaz */
{
    int i;
    for (i = n / 2; i >= 0; i--)
        Refaz(n, vet, i); /* chama método refaz p/ cada nó antes de n/2 */
}

void Imprimevetor(int n, int *vet) /* imprime o vetor */
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", vet[i]);
    printf("\n");
}

void HeapSort(int n, int *vet) /* ordena */
{
    int i, aux;
    for (i = 0; i < n - 1; i++)
    {
        /* faz a troca */
        aux = vet[0];
        vet[0] = vet[n - (i + 1)];
        vet[n - (i + 1)] = aux;
        Refaz(n - (i + 1), vet, 0); /* note que analisamos até o caso i= n-2 */
        Imprimevetor(n, vet);
    }
}

int main()
{
    int n, i, *vet;
    scanf("%d", &n);                      /* leitura do tamanho */
    vet = (int *)malloc(sizeof(int) * n); /* aloca memoria */
    for (i = 0; i < n; i++)               /* faz a leitura dos elementos */
        scanf("%d", &vet[i]);

    Refaz(n, vet, 0); /* refaz pela primeira vez */
    Constroi(n, vet); /* constroi o heap */
    Imprimevetor(n, vet);
    HeapSort(n, vet); /* ordena */

    free(vet); /* libera a memoria alocada */
    return 0;
}
