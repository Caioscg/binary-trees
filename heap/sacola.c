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

int checkFila(int adiciona[], int remove) {
    if (remove == adiciona[0]) return 1;
    else return 0;
}

int checkPilha(int adiciona[], int remove, int tamanhoA) {
    if (remove == adiciona[tamanhoA-1]) return 1;
    else return 0;
}

int checkFilaPrioridade(int adiciona[], int remove, int tamanhoA) {
    int j, contador = 0;

    for (j = 0; j < tamanhoA; j++) {
        if (remove >= adiciona[j]) contador++;
    }

    if (contador == tamanhoA) return 1;
    else return 0;
}

int checkIfPossible(int adiciona[], int remove, int tamanhoA) {
    int j, contador = 0;

    for (j = 0; j < tamanhoA; j++) {
        if (remove == adiciona[j]) contador++;
    }

    if (contador!= 0) return 1;
    else return 0;
}

int comparaVetores(int adiciona[], int remove, int tamanhoA) {
    int fila, pilha, filaPrioridade, i = 0, j = 0, possible;

    possible = checkIfPossible(adiciona, remove, tamanhoA);

    if (!possible) return 4;

    fila = checkFila(adiciona, remove);
    pilha = checkPilha(adiciona, remove, tamanhoA);
    filaPrioridade = checkFilaPrioridade(adiciona, remove, tamanhoA);

    if (fila && !pilha && !filaPrioridade) return 1;
    else if (pilha && !fila && !filaPrioridade) return 2;
    else if (filaPrioridade && !fila && !pilha) return 3;
    else if (!filaPrioridade && !fila && !pilha) return 4;
    else {
        if (fila && pilha && filaPrioridade) return 5;
        else if (!fila && pilha && filaPrioridade) return 6;
        else if (fila && !pilha && filaPrioridade) return 7;
        else if (fila && pilha && !filaPrioridade) return 8;
    }
}

int main() {
    int contador, funcao, numero, i, j, aux, tamanho, novoTamanho;
    char resposta;

    while (scanf("%d", &contador) != EOF) {
        int vetorAdiciona[1000], tipo[1000];
        int isFila=1, isPilha=1, isFilaPrioridade=1, impossible = 0;
        int* vetorNovo;
        i = 0, tamanho = 0;
        j = 0;
        aux = 0;

        while (aux < contador) {

            scanf("%d %d", &funcao, &numero);
            aux++;

            if (funcao == 1) {
                vetorAdiciona[i] = numero;

                i++;
                tamanho++;
            }

            else if (funcao == 2) {
                tipo[j] = comparaVetores(vetorAdiciona, numero, i);
                vetorNovo = remover(vetorAdiciona, tamanho, numero, &novoTamanho);

                i--;
                tamanho = novoTamanho;

                for (int w = 0; w < novoTamanho; w++) {
                    vetorAdiciona[w] = vetorNovo[w];
                }

                j++;
            }

        }

        for (i = 0; i < j; i++) {
            if (tipo[i]==4) {
                impossible = 1;
                break;
            }
            else if (tipo[i] == 1 && isFila != 0) {
                isFila = 1;
                isPilha = 0;
                isFilaPrioridade = 0;
            }
            else if (tipo[i] == 2 && isPilha != 0) {
                isPilha = 1;
                isFilaPrioridade = 0;
                isFila = 0;
            }
            else if (tipo[i] == 3 && isFilaPrioridade != 0) {
                isFilaPrioridade = 1;
                isFila = 0;
                isPilha = 0;
            }
            else if (tipo[i] == 6) {
                isFila = 0;
            }
            else if (tipo[i] == 7) {
                isPilha = 0;
            }
            else if (tipo[i] == 8) {
                isFilaPrioridade = 0;
            }
        }

        if (impossible) printf("impossible\n");
        else if (isFila && !isPilha && !isFilaPrioridade) printf("queue\n");
        else if (isPilha && !isFila && !isFilaPrioridade) printf("stack\n");
        else if (isFilaPrioridade && !isFila && !isPilha) printf("priority queue\n");
        else printf("not sure\n");

    }

}