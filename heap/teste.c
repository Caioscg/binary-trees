#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int livre;
} Funcionario;

int pai(int i);
int filhoEsquerda(int i);
int filhoDireita(int i);

int verificaMaiorFuncionario(Funcionario a, Funcionario b);

void reHeapUp(Funcionario *heap, int i);
void reHeapDown(Funcionario *heap, int i, int tamanho);
void insere(Funcionario *heap, int livre, int id, int *tamanho);
int deleta(Funcionario *heap, int *tamanho);

int maior(int a, int b);


int main() {

    int funcionariosTotal, clientesTotal;
    int i;
    int funcionarioTempo[10000];

    scanf("%d %d", &funcionariosTotal, &clientesTotal);

    for(i = 0; i < funcionariosTotal; i++) {
        scanf("%d%*c", &funcionarioTempo[i]);
    }

    int total = 0;
  
    Funcionario heap[funcionariosTotal];
    int tamanho = 0;
    for(i = 0; i < funcionariosTotal; i++) insere(heap, 0, i, &tamanho);

    while(clientesTotal--) {
        int clienteItens;
        scanf("%d%*c", &clienteItens);
        int id = heap[0].id;
        int livre = heap[0].livre;
        deleta(heap, &tamanho);
        insere(heap, (livre + funcionarioTempo[id] * clienteItens), id, &tamanho);
        total = maior(total, (livre + funcionarioTempo[id] * clienteItens));
    }

    printf("%d\n", total);

    return 0;
}

int pai(int i) {
    return (i - 1) / 2;
}

int filhoEsquerda(int i) {
    return 2 * i + 1;
}

int filhoDireita(int i) {
    return 2 * i + 2;
}

void reHeapUp(Funcionario *heap, int i) {
    Funcionario aux;

    while (i > 0 && !verificaMaiorFuncionario(heap[i], heap[pai(i)])) {
        aux = heap[i];
        heap[i] = heap[pai(i)];
        heap[pai(i)] = aux;
        
        i = pai(i);
    }
}

void reHeapDown(Funcionario *heap, int i, int tamanho) {
    int maior = i;

    if (filhoEsquerda(i) < tamanho && !verificaMaiorFuncionario(heap[filhoEsquerda(i)], heap[maior])) {
        maior = filhoEsquerda(i);
    }

    if (filhoDireita(i) < tamanho && !verificaMaiorFuncionario(heap[filhoDireita(i)], heap[maior])) {
        maior = filhoDireita(i);
    }

    if (maior != i) {
        Funcionario aux;
        
        aux = heap[i];
        heap[i] = heap[maior];
        heap[maior] = aux;

        reHeapDown(heap, maior, tamanho);
    }
}

void insere(Funcionario *heap, int livre, int id, int *tamanho) {
    heap[*tamanho].livre = livre;
    heap[*tamanho].id = id;
    reHeapUp(heap, *tamanho);
    (*tamanho)++;
}

int deleta(Funcionario *heap, int *tamanho) {
    int maior = heap[0].livre;
    heap[0] = heap[*tamanho - 1];
    (*tamanho)--;
    reHeapDown(heap, 0, *tamanho);

    return maior;
}

int verificaMaiorFuncionario(Funcionario a, Funcionario b){
    if(a.livre > b.livre) return 1;
    if(a.livre < b.livre) return 0;
    if(a.livre == b.livre && a.id > b.id) return 1;
    return 0;
}

int maior(int a, int b) {
    if(b > a) return b;
    return a;
}