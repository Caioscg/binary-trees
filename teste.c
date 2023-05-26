#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Definição da estrutura de um nó da árvore
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Função para criar um novo nó
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Erro ao alocar memória para um novo nó.\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Função para inserir um nó na árvore
Node* insertNode(Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    } else {
        if (data <= root->data) {
            root->left = insertNode(root->left, data);
        } else {
            root->right = insertNode(root->right, data);
        }
        return root;
    }
}

// Função para imprimir a árvore em BFS
void printBFS(Node* root) {
    if (root == NULL) {
        return;
    }

    // Criação de uma fila para realizar a busca em largura
    Node* queue[1000];
    int front = 0;
    int rear = 0;

    queue[rear++] = root;

    while (1) {
        Node* current = queue[front++];
        printf("%d", current->data);

        if (current->left != NULL) {
            queue[rear++] = current->left;
        }

        if (current->right != NULL) {
            queue[rear++] = current->right;
        }

        if (front >= rear) {
            break;
        }
        printf(" ");
    }
}

// Função principal
int main() {
    int c, n, i = 1, num;

    scanf("%d", &c);
    while (c) {
        Node* root = NULL;
        scanf("%d%*c", &n);

        while (n) {
            scanf("%d", &num);
            root = insertNode(root, num);
            n--;
        }
        printf("Case %d:\n", i);
        printBFS(root);
        printf("\n\n");

        i++;
        c--;
    }

    return 0;
}
