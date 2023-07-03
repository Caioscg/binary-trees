#include <stdio.h>

typedef struct {
    int raiz;
    int tamanho;
} Union;

int acharRaiz(Union bancos[], int x) {  // função para achar o representante do grupo
    if (bancos[x].raiz != x) {
        bancos[x].raiz = acharRaiz(bancos, bancos[x].raiz);
    }
    return bancos[x].raiz;
}

void unionBancos(Union bancos[], int x, int y) {  // função para unir bancos
    int raizX = acharRaiz(bancos, x);
    int raizY = acharRaiz(bancos, y);
    
    if (raizX == raizY)   // já estão unidos
        return;

    // União por tamanho (união sempre ocorre com o conjunto de menor tamanho sendo anexado ao de maior tamanho)
    if (bancos[raizX].tamanho < bancos[raizY].tamanho) {
        bancos[raizX].raiz = raizY;
        bancos[raizY].tamanho += bancos[raizX].tamanho;
    }
    else {
        bancos[raizY].raiz = raizX;
        bancos[raizX].tamanho += bancos[raizY].tamanho;
    }
}

void criaGrupo (Union bancos[], int n) {  // função que inicia cada banco como um grupo
    for (int i = 1; i <= n; i++) {
        bancos[i].raiz = i;
        bancos[i].tamanho = 1;
    }
}

int main() {
    int nBancos, nOperacoes, bancoA, bancoB;
    char operacao;

    scanf("%d %d%*c", &nBancos, &nOperacoes);

    Union bancos[100000];
    criaGrupo(bancos, nBancos);

    for (int i = 0; i < nOperacoes; i++) {
        scanf("%c %d %d%*c", &operacao, &bancoA, &bancoB);

        if (operacao == 'F') {  // fusão de bancos
            unionBancos(bancos, bancoA, bancoB);
        } 
        else if (operacao == 'C') {  // consulta de bancos
            if (acharRaiz(bancos, bancoA) == acharRaiz(bancos, bancoB))  // mesmo representante
                printf("S\n");
            else
                printf("N\n");
        }
    }
    return 0;
}