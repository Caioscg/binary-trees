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

int checkFila(int adiciona[], int remove[] , int tamanhoR) {
    int i = 0, contador = 0;

    while(i < tamanhoR) {
        if (adiciona[i] == remove[i]) contador++;
        i++;
    }

    if (contador == i) return 1;
    else return 0;
}

int checkPilha(int adiciona[], int remove[], int tamanhoA , int tamanhoR) {
    int i = 0, contador = 0;

    while(i < tamanhoR) {
        if (adiciona[tamanhoA-1] == remove[i]) contador++;
        i++;
        tamanhoA--;
    }

    if (contador == i) return 1;
    else return 0;
}

int checkFilaPrioridade(int adiciona[], int remove[], int tamanhoA , int tamanhoR) {
    int i, j, contador = 0, aux = 0, k;

    for (i = 0; i < tamanhoR; i++) {
        k = 0;

        for (j = 0; j < tamanhoA; j++) {
            if (remove[i] >= adiciona[j]) k++;
        }

        if (k == tamanhoA-aux) contador++;
        aux++;
    }
    if (contador == tamanhoR) return 1;
    else return 0;
}

int checkIfPossible(int adiciona[], int remove[], int tamanhoA, int tamanhoR) {
    int i, j, aux, contador = 0;

    for (i = 0; i < tamanhoR; i++) {
        aux = 0;
        for (j = 0; j < tamanhoA; j++) {
            if (remove[i] == adiciona[j]) aux++;
        }

        if (aux!= 0) contador++;
    }

    if (contador == tamanhoR) return 1;
    else return 0;
}

int comparaVetores(int adiciona[], int remove[], int tamanhoA, int tamanhoR) {
    int fila, pilha, filaPrioridade, i = 0, j = 0, possible;

    possible = checkIfPossible(adiciona, remove, tamanhoA, tamanhoR);

    if (!possible) return 4;

    fila = checkFila(adiciona, remove, tamanhoR);
    pilha = checkPilha(adiciona, remove, tamanhoA, tamanhoR);
    filaPrioridade = checkFilaPrioridade(adiciona, remove, tamanhoA, tamanhoR);

    //printf("fila: %d\npilha: %d\nfilaPrioridade: %d", fila, pilha, filaPrioridade);

    if (fila && !pilha && !filaPrioridade) return 1;
    else if (pilha && !fila && !filaPrioridade) return 2;
    else if (filaPrioridade && !fila && !pilha) return 3;
    else if (!filaPrioridade && !fila && !pilha) return 4;
    else return 5;
}

int main() {
    int contador, funcao, numero, i, j, aux, tamanho, novoTamanho, k;
    char resposta;

    while (scanf("%d", &contador) != EOF) {
        int vetorAdiciona[1000], vetorRemove[1000], tipo[1000];
        int fila=0, pilha=0, filaPrioridade=0, notSure = 0;
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
                vetorRemove[j] = numero;

                tipo[j] = comparaVetores(vetorAdiciona, vetorRemove, i, j);
                vetorNovo = remover(vetorAdiciona, tamanho, numero, &novoTamanho);
                
                printf("\nVetor original: ");
                for (int w = 0; w < tamanho; w++) {
                    printf("%d ", vetorAdiciona[w]);
                }
                printf("\n");

                tamanho = novoTamanho;

                printf("\nNovo vetor: ");
                for (int w = 0; w < novoTamanho; w++) {
                    vetorAdiciona[w] = vetorNovo[w];
                    printf("%d ", vetorAdiciona[w]);
                }
                printf("\n");

                j++;
            }
            

        }

        for (i = 0; i < j-1; i++) {
            if (tipo[i]==4 || tipo[i+1]==4) {
                //printf("impossible1\n");
                break;
            }
            else if (tipo[i] != tipo[i+1]) {
                if (tipo[i] == 5) {
                    if(tipo[i+1] == 1) fila++;
                    else if(tipo[i+1] == 2) pilha++;
                    else if(tipo[i+1] == 3) filaPrioridade++;
                }
                else if (tipo[i+1] == 5) {
                    if(tipo[i] == 1) fila++;
                    else if(tipo[i] == 2) pilha++;
                    else if(tipo[i] == 3) filaPrioridade++;
                }
                else {
                    //printf("impossible2\n");
                    break;
                }
            }
            else if (tipo[i] == tipo[i+1]) {
                if (tipo[i] == 1) fila++;
                else if (tipo[i] == 2) pilha++;
                else if (tipo[i] == 3) filaPrioridade++;
                else if (tipo[i] == 5) notSure++;
            }
        }

        //if (fila && !pilha && !filaPrioridade) printf("queue\n");
        //else if (pilha && !fila && !filaPrioridade) printf("stack\n");
        //else if (filaPrioridade && !fila && !pilha) printf("priority queue\n");
        //else printf("not sure\n");

    }


}