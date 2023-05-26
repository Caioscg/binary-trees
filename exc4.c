#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No{
    int numero;
    struct No *esquerda;
    struct No *direita;
}No;

void criartree(No **pRaiz)
{
    *pRaiz = NULL;
}

void insercao(No **pRaiz, int numero2)
{
	if (*pRaiz == NULL)
	{
	      *pRaiz=(No *)malloc(sizeof (No));
	      (*pRaiz)->esquerda=NULL;
	      (*pRaiz)->direita=NULL;
	      (*pRaiz)->numero=numero2;
	}
	else 
        {
		if (numero2 < ((*pRaiz)->numero))
		{
			insercao(&((*pRaiz)->esquerda), numero2);
		}
		else
		{
			insercao(&((*pRaiz)->direita), numero2);
		}
	}
}

void exibirEmOrdem(No *pRaiz, int *isFirst){
    if(pRaiz != NULL){
        exibirEmOrdem(pRaiz->esquerda, isFirst);
        if(*isFirst) {
            printf("%i", pRaiz->numero);
            *isFirst = 0;
        }
        else {
            printf(" %i", pRaiz->numero);
        }
        exibirEmOrdem(pRaiz->direita, isFirst);
    }
}

void exibirPreOrdem(No *pRaiz, int *isFirst){
    if(pRaiz != NULL){
        if(*isFirst) {
            printf("%i", pRaiz->numero);
            *isFirst = 0;
        }
        else {
            printf(" %i", pRaiz->numero);
        }
        exibirPreOrdem(pRaiz->esquerda, isFirst);
        exibirPreOrdem(pRaiz->direita, isFirst);
    }
}

void exibirPosOrdem(No *pRaiz, int *isFirst){
    if(pRaiz != NULL){
        exibirPosOrdem(pRaiz->esquerda, isFirst);
        exibirPosOrdem(pRaiz->direita, isFirst);
        if(*isFirst) {
            printf("%i", pRaiz->numero);
            *isFirst = 0;
        }
        else {
            printf(" %i", pRaiz->numero);
        }
    }
}

int verificaelement(int element, No *tree){
    if(tree) {
        if(element == tree->numero) {
            return 1;
        }
        else if(element < tree->numero) {
            return verificaelement(element, tree->esquerda);
        }
        else {
            return verificaelement(element, tree->direita);
        }
    }
    return 0;
}

No* removerelement(No *raiz, int chave) {
    if(raiz == NULL) {
        return NULL;
    } else { // procura o nó a remover
        if(raiz->numero == chave) {
            // remove nós folhas (nós sem filhos)
            if(raiz->esquerda == NULL && raiz->direita == NULL) {
                free(raiz);
                return NULL;
            }
            else {
                // remover nós que possuem 2 filhos
                if(raiz->esquerda != NULL && raiz->direita != NULL) {
                    No *aux = raiz->esquerda;
                    while(aux->direita != NULL){
                        aux = aux->direita;
                    }
                    raiz->numero = aux->numero;
                    aux->numero = chave;
                    raiz->esquerda = removerelement(raiz->esquerda, chave);
                    return raiz;
                }
                else{
                    // remover nós que possuem apenas 1 filho
                    No *aux;
                    if(raiz->esquerda != NULL)
                        aux = raiz->esquerda;
                    else
                        aux = raiz->direita;
                    free(raiz);
                    return aux;
                }
            }
        } else {
            if(chave < raiz->numero)
                raiz->esquerda = removerelement(raiz->esquerda, chave);
            else
                raiz->direita = removerelement(raiz->direita, chave);
            return raiz;
        }
    }
}
 
int main() {
 
    char promptStr[8];
    int  promptNum;
    No **tree = (struct No**)malloc(sizeof(struct No*));
    criartree(tree);
    while(scanf("%s", promptStr) != EOF){
        // printf("%s\n", promptStr);
        if(strcmp(promptStr, "PREFIXA") == 0) {
            int isFirst = 1;
            exibirPreOrdem(*tree, &isFirst);
            printf("\n");
        }
        else if(strcmp(promptStr, "INFIXA") == 0) {
            int isFirst = 1;
            exibirEmOrdem(*tree, &isFirst);
            printf("\n");
        }
        else if(strcmp(promptStr, "POSFIXA") == 0) {
            int isFirst = 1;
            exibirPosOrdem(*tree, &isFirst);
            printf("\n");
        }
        else {
            scanf("%d", &promptNum);
            // printf("%d\n", promptNum);
            if(promptStr[0] == 'I') insercao(tree, promptNum);
            if (promptStr[0] == 'P') {
                if(verificaelement(promptNum, *tree) == 0) {
                    printf("%d nao existe\n", promptNum);
                } else {
                    printf("%d existe\n", promptNum);
                }
            }
            if(promptStr[0] == 'R') *tree = removerelement(*tree, promptNum);
        }
    }
 
    return 0;
}