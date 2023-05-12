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

void imprimirPre(No *raiz) {
    if(raiz != NULL) {
        printf(" %d", raiz->conteudo);
        imprimirPre(raiz->esquerda);
        imprimirPre(raiz->direita);
    }
}

void imprimirIn(No *raiz) {
    if(raiz != NULL) {
        imprimirIn(raiz->esquerda);
        printf(" %d", raiz->conteudo);
        imprimirIn(raiz->direita);
    }
}

void imprimirPos(No *raiz) {
    if(raiz !=NULL) {
        imprimirPos(raiz->esquerda);
        imprimirPos(raiz->direita);
        printf(" %d", raiz->conteudo);
    }
}

int main() {
    int c, n, valor, i = 1;

    No *raiz = (No *)malloc(sizeof(No *));
    scanf("%d", &c);

    while (c) {
        No *raiz = NULL;
        scanf("%d%*c", &n);

        while (n) {
            scanf("%d%*c", &valor);

            raiz = inserir(raiz, valor);
            n--;
        }
        printf("Case %d:\n", i);

        printf("Pre.:");
        imprimirPre(raiz);
        printf("\n");
        printf("In..:");
        imprimirIn(raiz);
        printf("\n");
        printf("Post:");
        imprimirPos(raiz);

        i++;
        c--;

        printf("\n\n");
    }

    return 0;
}

