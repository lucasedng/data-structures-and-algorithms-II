//Lucas Eduardo Nogueira Gon�alves, 122055 (Integral)
#include <stdio.h>
#include <stdlib.h>

void Imprimevetor(int n, int *vet) /* fun��o de impress�o */
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", vet[i]);
    printf("\n"); /* pula uma linha */
}

int EncontraMaior(int n, int *vet) /* fun��o que encontra o maior elemento */
{
    int i, maior, aux;
    maior = vet[0];         /* primeira posi��o do vetor */
    for (i = 1; i < n; i++) /* percorre todo o vetor */
        if (vet[i] > maior)
            maior = vet[i]; /* troca quando encontrar o maior elemento */
    return maior;
}

int *InicializaContador(int maior) /* fun��o que inicializa o contador com 0 */
{
    int i, *vetcont;
    vetcont = (int *)malloc(sizeof(int) * (maior + 1)); /* vai de 0 at� o maior elemento */
    for (i = 0; i < maior + 1; i++)
        vetcont[i] = 0; /* a contagem inicia no zero */
    return vetcont;
}

void CountingSort(int n, int *vet, int *vetaux, int exp) /* countingsort modificado */
{
    int i, maior, *vetcont, *vetdivid;
    vetdivid = (int *)malloc(sizeof(int) * n); /* vetor que ira armazernar cada digito (unidade, dezena, centena, ...) */
    for (i = 0; i < n; i++)
        vetdivid[i] = (vet[i] / exp) % 10; /* armazena tal posi��o */

    maior = EncontraMaior(n, vetdivid); /* encontra o maior elemento (note que o max � 9) */

    vetcont = InicializaContador(maior); /* inicia o novo contador com 0 */

    for (i = 0; i < n; i++)
        vetcont[vetdivid[i]] += 1; /* verifica onde cada um inicia */

    for (i = 1; i <= maior; i++)
        vetcont[i] += vetcont[i - 1]; /* soma acumulada */

    for (i = n - 1; i >= 0; i--)
    {
        vetcont[vetdivid[i]]--;                /* o contador na posi��o do elemento decresce */
        vetaux[vetcont[vetdivid[i]]] = vet[i]; /* ordena (vetaux vai carregar o vetor ordenado) */
    }
    for (i = 0; i < n; i++)
        vet[i] = vetaux[i]; /* como vamos precisar do vet novamente, atualizamos as novas posi��es */

    free(vetdivid); /* libera os dois vetores alocados na fun��o */
    free(vetcont);
}

int EncontraDigito(int n, int *vet) /* encontra a quantidade de digitos do maior elemento */
{
    int i, d, maior;
    i = 1;
    d = 1;
    maior = EncontraMaior(n, vet); /* pega o maior elemento do vetor */
    while (maior / i != 0)         /* enquanto a divis�o por potencias de 10 n�o for zero vamos somando 1 no contador*/
    {
        i *= 10;
        d++;
    }
    return d; /* retorna quantas vezes dividimos por 10 e � equivalente ao numero de digitos */
}

void RadixSort(int d, int n, int *vet, int *vetaux) /* RadixSort */
{
    int i, exp;
    exp = 1;                /* sera equivalente as potencias de 10 */
    for (i = 1; i < d; i++) /* ordenamos at� o numero de digitos */
    {
        CountingSort(n, vet, vetaux, exp); /* ordena��o por counting */
        exp *= 10;                         /* atualiza a potencia */
        Imprimevetor(n, vetaux);           /* imprime o vetor "ordenado" */
    }
}

int main()
{
    int i, n, d, maior, *vet, *vetaux;
    scanf("%d", &n);                         /* leitura do tamanho */
    vet = (int *)malloc(sizeof(int) * n);    /* alocac��o do vetor principal */
    vetaux = (int *)malloc(sizeof(int) * n); /* aloca��o do auxiliar */
    for (i = 0; i < n; i++)
        scanf("%d", &vet[i]);     /* leitura dos elementos */
    d = EncontraDigito(n, vet);   /* encontra o numero de digitos */
    RadixSort(d, n, vet, vetaux); /* ordena��o por radix */

    free(vetaux); /* libera os vetores */
    free(vet);
    return 0;
}
