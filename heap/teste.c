#include <stdio.h>
#include <stdlib.h>

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

    printf("fila: %d\npilha: %d\nfilaPrioridade: %d", fila, pilha, filaPrioridade);

    if (fila && !pilha && !filaPrioridade) return 1;
    else if (pilha && !fila && !filaPrioridade) return 2;
    else if (filaPrioridade && !fila && !pilha) return 3;
    else if (!filaPrioridade && !fila && !pilha) return 4;
    else return 5;
}

int main() {
    int contador, funcao, numero, i, j, aux, tipo;
    char resposta;

    while (scanf("%d", &contador) != EOF) {
        int vetorAdiciona[1000];
        int vetorRemove[1000];
        i = 0;
        j = 0;
        aux = 0;

        while (aux < contador) {

            scanf("%d %d", &funcao, &numero);
            aux++;

            if (funcao == 1) {
                vetorAdiciona[i] = numero;
                i++;
            }

            else if (funcao == 2) {
                vetorRemove[j] = numero;
                j++;
            }
            
        }

        tipo = comparaVetores(vetorAdiciona, vetorRemove, i, j);

        if (tipo == 1) printf("queue\n");
        else if (tipo == 2) printf("stack\n");
        else if (tipo == 3) printf("priority queue\n");
        else if (tipo == 4) printf("impossible\n");
        else if (tipo == 5) printf("not sure\n");

    }

}