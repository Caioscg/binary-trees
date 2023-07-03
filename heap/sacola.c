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

int checkFila(int adiciona[], int remove) { // verifica se pode ser fila
    if (remove == adiciona[0]) return 1; // verifica se o elemento é o primeiro do array
    else return 0;
}

int checkPilha(int adiciona[], int remove, int tamanhoA) { // verifica se pode ser pilha
    if (remove == adiciona[tamanhoA-1]) return 1; // verifica se o elemento é o ultimo do array
    else return 0;
}

int checkFilaPrioridade(int adiciona[], int remove, int tamanhoA) { // verifica se pode ser fila de prioridade
    int j, contador = 0;

    for (j = 0; j < tamanhoA; j++) {
        if (remove >= adiciona[j]) contador++;  // verifica se o elemento é o maior do array
    }

    if (contador == tamanhoA) return 1;
    else return 0;
}

int checkIfPossible(int adiciona[], int remove, int tamanhoA) {  // verifica se o numero para remover existe no array
    int j, contador = 0;

    for (j = 0; j < tamanhoA; j++) {
        if (remove == adiciona[j]) contador++;
    }

    if (contador!= 0) return 1;
    else return 0;
}

int comparaVetores(int adiciona[], int remove, int tamanhoA) {
    int fila, pilha, filaPrioridade, i = 0, j = 0, possible;

    possible = checkIfPossible(adiciona, remove, tamanhoA);  // verifica se é possível

    if (!possible) return 4;

    fila = checkFila(adiciona, remove);
    pilha = checkPilha(adiciona, remove, tamanhoA);
    filaPrioridade = checkFilaPrioridade(adiciona, remove, tamanhoA);

    if (fila && !pilha && !filaPrioridade) return 1;         // só pode ser fila nessa remoção
    else if (pilha && !fila && !filaPrioridade) return 2;    // só pode ser pilha nessa remoção
    else if (filaPrioridade && !fila && !pilha) return 3;    // só pode ser fila de prioridade nessa remoção
    else if (!filaPrioridade && !fila && !pilha) return 4;   // nenhuma das estruturas
    else {
        if (fila && pilha && filaPrioridade) return 5;       // só pode ser todos nessa remoção
        else if (!fila && pilha && filaPrioridade) return 6; // só pode ser pilha ou fila de prioridade nessa remoção
        else if (fila && !pilha && filaPrioridade) return 7; // só pode ser fila ou fila de prioridade nessa remoção
        else if (fila && pilha && !filaPrioridade) return 8; // só pode ser fila ou pilha nessa remoção
    }
}

int main() {
    int contador, funcao, numero, i, j, aux, tamanho, novoTamanho;
    char resposta;

    while (scanf("%d", &contador) != EOF) {
        int vetorAdiciona[1000], remocao[1000];
        int isFila=1, isPilha=1, isFilaPrioridade=1, impossible = 0;
        int* vetorNovo;
        i = 0, tamanho = 0;
        j = 0;
        aux = 0;

        while (aux < contador) {

            scanf("%d %d", &funcao, &numero);
            aux++;

            if (funcao == 1) {  // adicionar
                vetorAdiciona[i] = numero;

                i++;
                tamanho++;
            }

            else if (funcao == 2) {  // remover
                remocao[j] = comparaVetores(vetorAdiciona, numero, i);   // verifica as possibilidades
                vetorNovo = remover(vetorAdiciona, tamanho, numero, &novoTamanho);  // remove o elemento

                i--;
                tamanho = novoTamanho;

                for (int w = 0; w < novoTamanho; w++) {  // atualiza o vetor
                    vetorAdiciona[w] = vetorNovo[w];
                }

                j++;
            }

        }

        for (i = 0; i < j; i++) {
            if (remocao[i]==4) {
                impossible = 1;
                break;
            }
            else if (remocao[i] == 1 && isFila != 0) {
                isFila = 1;
                isPilha = 0;
                isFilaPrioridade = 0;
            }
            else if (remocao[i] == 2 && isPilha != 0) {
                isPilha = 1;
                isFilaPrioridade = 0;
                isFila = 0;
            }
            else if (remocao[i] == 3 && isFilaPrioridade != 0) {
                isFilaPrioridade = 1;
                isFila = 0;
                isPilha = 0;
            }
            else if (remocao[i] == 6) {
                isFila = 0;
            }
            else if (remocao[i] == 7) {
                isPilha = 0;
            }
            else if (remocao[i] == 8) {
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