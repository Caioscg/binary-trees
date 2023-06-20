#include <stdio.h>
#include <stdlib.h>

int* remover(int vetor[], int tamanho, int numero, int* novoTamanho) {
    int i, j;
    int encontrado = 0; // Variável para indicar se o número foi encontrado

    // Verificar se o número está presente no vetor
    for (i = 0; i < tamanho; i++) {
        if (vetor[i] == numero) {
            encontrado = 1;
            break;
        }
    }

    // Se o número não foi encontrado, retornar o vetor original
    if (!encontrado) {
        *novoTamanho = tamanho;
        return vetor;
    }

    // Criar um novo vetor com tamanho reduzido
    int* novoVetor = (int*)malloc((tamanho - 1) * sizeof(int));

    // Copiar os elementos do vetor original para o novo vetor, excluindo o número a ser removido
    for (i = 0, j = 0; i < tamanho; i++) {
        if (vetor[i] != numero) {
            novoVetor[j] = vetor[i];
            j++;
        }
    }

    // Definir o novo tamanho do vetor
    *novoTamanho = tamanho - 1;

    // Retornar o novo vetor
    return novoVetor;
}

int main() {

    int vetor[] = {1, 2, 3, 4, 5};
    int tamanho = 5;
    int numero;
    int novoTamanho;

    while (1) {
        scanf("%d", &numero);
        int* novoVetor = remover(vetor, tamanho, numero, &novoTamanho);

        printf("Vetor original: ");
        for (int i = 0; i < tamanho; i++) {
            printf("%d ", vetor[i]);
        }
        printf("\n");

        tamanho = novoTamanho;
        
        printf("Novo vetor: ");
        for (int i = 0; i < novoTamanho; i++) {
            printf("%d ", novoVetor[i]);
            vetor[i] = novoVetor[i];
        }
        printf("\n");
    }

    return 0;
}
