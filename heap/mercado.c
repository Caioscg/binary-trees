#include <stdlib.h>
#include <stdio.h>

int calcFuncionario(int tempo[], int tamanho, int livre) { // calcula o tempo dos funcionarios
    int i, maiorPosicao = 0, menorPosicao = 0;

    if (livre == 1) {  // procura o funcionario livre
        for (i = 1; i < tamanho; i++) {
            if (tempo[i] < tempo[menorPosicao]) menorPosicao = i;
        }
        return menorPosicao;
    }
    else {   // procura o maior tempo
        for (i = 1; i < tamanho; i++) {
            if (tempo[i] > tempo[maiorPosicao]) maiorPosicao = i;
        }
        return maiorPosicao;
    }
}

int calcTempo(int funcionarios[], int produtos[], int Nfuncionarios, int Nclientes) {

    int i, j = 0, *tempo, funcionarioLivre, tempoTotal;
    tempo = (int *) calloc(Nfuncionarios, sizeof(int)); // cria o vetor tempo[Nfuncionarios] já zerados

    while (j < Nfuncionarios) {  // poem todos os funcionarios pra trabalhar ao mesmo tempo
        tempo[j] += funcionarios[j]*produtos[j];
        j++;
    }

    for (j; j < Nclientes; j++) {
        funcionarioLivre = calcFuncionario(tempo, Nfuncionarios, 1);  // após a 1 rodada de todos, procura quem ta livre
        tempo[funcionarioLivre] += funcionarios[funcionarioLivre] * produtos[j]; //coloca quem ta livre para trabalhar
    }

    tempoTotal = tempo[calcFuncionario(tempo, Nfuncionarios, 2)];  // posição do funcionario que levou mais tempo

    return tempoTotal;
}

int main () {
    int Nfuncionarios, *funcionarios, Nclientes, *produtos, i, j;
    int tempo = 0;

    scanf("%d %d", &Nfuncionarios, &Nclientes);  // scan de numero de funcionarios e clientes

    funcionarios = (int *) malloc(Nfuncionarios * sizeof(int));
    produtos = (int *) malloc(Nclientes * sizeof(int));

    for (i = 0; i < Nfuncionarios; i++) {
        scanf("%d", &funcionarios[i]);    // scan do tempo que cada funcionario leva por produto
    }

    for (j = 0; j < Nclientes; j++) {
        scanf("%d", &produtos[j]);     // scan da quantidade de produtos por cliente
    }

    tempo = calcTempo(funcionarios, produtos, Nfuncionarios, Nclientes);  // retorna o funcionario que levou mais tempo
    printf("%d\n", tempo);

    return 0;
}