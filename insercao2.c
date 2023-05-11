#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int conteudo;
    struct no *direita, * esquerda;
} No;

No* inserir(No *raiz, int valor) {
    if(raiz == NULL) {
        No *novo = (No*)malloc(sizeof(No));
        novo->conteudo = valor;
        novo->direita = NULL;
        novo->esquerda = NULL;
        return novo;
    }
    else {
        if(valor < raiz->conteudo)
            raiz->esquerda = inserir(raiz->esquerda, valor);
        if(valor > raiz->conteudo)
            raiz->direita = inserir(raiz->direita, valor);
        return raiz;
    }
}

void imprimir(No *raiz) {
    if(raiz != NULL) {
        imprimir(raiz->esquerda);
        printf("%d ", raiz->conteudo);
        imprimir(raiz->direita);
    }
}

int main() {
    int op = 1, valor;
    
    No *raiz = NULL;

    while(op != 0) {
        printf("\n0 - sair\n1 - inserir\n2 - imprimir\n");
        scanf("%d", &op);

        switch (op)
        {
        case 0:
            printf("\nSaindo...\n");
            break;

        case 1:
            printf("Digite um valor: ");
            scanf("%d", &valor);
            raiz = inserir(raiz, valor);

            break;

        case 2:
            printf("\nImpressão da árvore binária:\n");
            imprimir(raiz);
            break;

        default:
            printf("\nOpção inválida!\n");
            break;
        }
    }
    printf("%d ", raiz->conteudo);
        if (raiz->esquerda != NULL) {
            imprimirPre(raiz->esquerda, root);
        }
        else if (raiz->direita != NULL) {
            imprimirPre(raiz->direita, root);
        }
        else {
            raiz = root;
            
            imprimirPre(raiz->direita, root);  
        }
}

