#include <stdio.h>

typedef struct {
    int raiz;
    int poder;

} Union;

void criaGrupo (Union guildas[], int poder, int n) {  // função que inicia cada banco como um grupo
        guildas[n].raiz = n;
        guildas[n].poder = poder;
}

int acharRaiz(Union guildas[], int x) {  // função para achar o representante do grupo
    if (guildas[x].raiz != x) {
        guildas[x].raiz = acharRaiz(guildas, guildas[x].raiz);
    }
    return guildas[x].raiz;
}

void unionGuildas(Union guildas[], int x, int y) {  // função para unir guildas
    int raizX = acharRaiz(guildas, x);
    int raizY = acharRaiz(guildas, y);
    
    if (raizX == raizY)   // já estão unidos
        return;

    // União por poder (união sempre ocorre com o conjunto de menor poder sendo anexado ao de maior poder)
    if (guildas[raizX].poder < guildas[raizY].poder) {
        guildas[raizX].raiz = raizY;
        guildas[raizY].poder += guildas[raizX].poder;
    }
    else {
        guildas[raizY].raiz = raizX;
        guildas[raizX].poder += guildas[raizY].poder;
    }
}

int main() {
    int nJogadores, nAcoes, jogadorA, jogadorB, poder, acao;
    int raizA, raizB, vitorias;

    while(1) {
        vitorias = 0;
        scanf("%d %d", &nJogadores, &nAcoes);
        if (!nJogadores && !nAcoes) return 0;

        Union guildas[100000];

        for (int i = 0; i < nJogadores; i++) {
            scanf("%d", &poder);
            criaGrupo(guildas, poder, i+1);
        }

        for (int i = 0; i < nAcoes; i++) {
            scanf("%d %d %d", &acao, &jogadorA, &jogadorB);

            if (acao == 1) {  // fusão de guildas
                unionGuildas(guildas, jogadorA, jogadorB);
            } 
            else if (acao == 2) {  // batalha de guildas
                raizA = acharRaiz(guildas, jogadorA);
                raizB = acharRaiz(guildas, jogadorB);

                if (raizA == acharRaiz(guildas, 1)) {   // verifica se o rafael faz parte mesma guilda do jogadorA
                    if (guildas[raizA].poder > guildas[raizB].poder) {  // verifica se a guilda do rafael tem mais poder
                        vitorias++;
                    }
                }
                else if (raizB == acharRaiz(guildas, 1)) {
                    if (guildas[raizB].poder > guildas[raizA].poder) {
                        vitorias++;
                    }
                }
            }
        }
        printf("%d\n", vitorias);
    }
    return 0;
}