#include "tps.h"
#define MAX 15

void grafo_para_tsp(int n, int grafo[MAX][MAX], int pesos[MAX][MAX]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                pesos[i][j] = 0;
            } else if (grafo[i][j]) {
                pesos[i][j] = 1;
            } else {
                pesos[i][j] = 2;
            }
        }
    }
}

/* Calcula o custo de um ciclo. */
int calcular_custo(int n, int pesos[MAX][MAX], int caminho[]) {
    int custo = 0;

    for (int i = 0; i < n - 1; i++) {
        custo += pesos[caminho[i]][caminho[i + 1]];
    }

    custo += pesos[caminho[n - 1]][caminho[0]];

    return custo;
}

/* Permuta os vertices para encontrar o menor ciclo. */
void permutar(int n, int pesos[MAX][MAX], int caminho[], int visitado[], int pos, int *melhor_custo, int melhor_caminho[]) {

    if (pos == n) {
        int custo = calcular_custo(n, pesos, caminho);

        if (custo < *melhor_custo) {
            *melhor_custo = custo;

            for (int i = 0; i < n; i++) {
                melhor_caminho[i] = caminho[i];
            }
        }

        return;
    }

    for (int v = 1; v < n; v++) {
        if (!visitado[v]) {
            caminho[pos] = v;
            visitado[v] = 1;

            permutar(n, pesos, caminho, visitado, pos + 1, melhor_custo, melhor_caminho);

            visitado[v] = 0;
        }
    }
}

int tsp_forca_bruta(int n, int pesos[MAX][MAX], int melhor_caminho[]) {
    int caminho[MAX];
    int visitado[MAX] = {0};
    int melhor_custo = 999999;

    caminho[0] = 0;
    visitado[0] = 1;

    permutar(n, pesos, caminho, visitado, 1,
             &melhor_custo, melhor_caminho);

    return melhor_custo;
}

/* Vizinho mais proximo. */
int tsp_vizinho_mais_proximo(int n, int pesos[MAX][MAX], int caminho[]) {
    int visitado[MAX] = {0};
    int custo = 0;

    caminho[0] = 0;
    visitado[0] = 1;

    for (int i = 1; i < n; i++) {
        int atual = caminho[i - 1];
        int menor = 999999;
        int escolhido = -1;

        for (int j = 1; j < n; j++) {
            if (!visitado[j] && pesos[atual][j] < menor) {
                menor = pesos[atual][j];
                escolhido = j;
            }
        }

        caminho[i] = escolhido;
        visitado[escolhido] = 1;
        custo += menor;
    }

    custo += pesos[caminho[n - 1]][0];

    return custo;
}

/* Insercao do mais proximo. */
int tsp_insercao(int n, int pesos[MAX][MAX], int caminho[]) {
    int visitado[MAX] = {0};
    int tamanho = 2;

    caminho[0] = 0;

    /* Escolhe o vertice mais proximo da origem. */
    int primeiro = 1;

    for (int i = 2; i < n; i++) {
        if (pesos[0][i] < pesos[0][primeiro]) {
            primeiro = i;
        }
    }

    caminho[1] = primeiro;
    visitado[0] = 1;
    visitado[primeiro] = 1;

    while (tamanho < n) {
        int escolhido = -1;
        int menor = 999999;

        /* Escolhe o vertice mais proximo do ciclo. */
        for (int v = 1; v < n; v++) {
            if (visitado[v]) {
                continue;
            }

            for (int i = 0; i < tamanho; i++) {
                if (pesos[v][caminho[i]] < menor) {
                    menor = pesos[v][caminho[i]];
                    escolhido = v;
                }
            }
        }

        /* Encontra a melhor posicao de insercao. */
        int posicao = 0;
        int menor_aumento = 999999;

        for (int i = 0; i < tamanho; i++) {
            int j = (i + 1) % tamanho;

            int aumento = pesos[caminho[i]][escolhido] + pesos[escolhido][caminho[j]] - pesos[caminho[i]][caminho[j]];

            if (aumento < menor_aumento) {
                menor_aumento = aumento;
                posicao = i + 1;
            }
        }

        for (int i = tamanho; i > posicao; i--) {
            caminho[i] = caminho[i - 1];
        }

        caminho[posicao] = escolhido;
        visitado[escolhido] = 1;
        tamanho++;
    }

    return calcular_custo(n, pesos, caminho);
}
