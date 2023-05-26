#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura de um nó da árvore
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Função para criar um novo nó da árvore

Node* inserir(Node *raiz, int valor) {
    if(raiz == NULL) {
        Node *novo = (Node*)malloc(sizeof(Node));
        novo->data = valor;
        novo->right = NULL;
        novo->left = NULL;
        return novo;
    }
    else {
        if(valor < raiz->data)
            raiz->left = inserir(raiz->left, valor);
        if(valor > raiz->data)
            raiz->right = inserir(raiz->right, valor);
        return raiz;
    }
}

// Função para imprimir a árvore binária usando BFS
void printBFS(Node* root) {
    if (root == NULL)
        return;

    // Criação de uma fila para armazenar os nós da árvore
    Node** queue = (Node**)malloc(sizeof(Node*));
    int front = 0;
    int rear = 0;

    // Enfileira o nó raiz
    queue[rear++] = root;

    while (front < rear) {
        // Desenfileira o nó atual e o imprime
        Node* currentNode = queue[front++];
        printf("%d ", currentNode->data);

        // Enfileira os nós filhos, se existirem
        if (currentNode->left != NULL)
            queue[rear++] = currentNode->left;
        if (currentNode->right != NULL)
            queue[rear++] = currentNode->right;
    }

    // Libera a memória alocada para a fila
    free(queue);
}

int main() {
    // Constrói uma árvore binária de exemplo
    int c, n, valor, j = 1;

    Node *raiz = NULL;
    scanf("%d", &c);

    while (c) {
        scanf("%d%*c", &n);

        while (n) {
            scanf("%d%*c", &valor);

            raiz = inserir(raiz, valor);
            n--;
        }
        printf("Case %d:\n", j);
        printBFS(raiz);

        j++;
        c--;

        printf("\n");
    }
    
    
    return 0;
}
