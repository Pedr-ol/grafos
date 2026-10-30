#include <stdio.h>
#include <time.h>
#include "hamiltoniano.h"
#include "tps.h"

#define MAX 15

void imprimir_caminho(int n, int caminho[]) {
    for (int i = 0; i < n; i++) {
        printf("%d ", caminho[i]);
    }

    printf("\n");
}

void gerar_grafo(int n, int grafo[MAX][MAX]) {
    /* Inicializa a matriz. */
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            grafo[i][j] = 0;
        }
    }

    /* Cria um ciclo. */
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        grafo[i][j] = 1;
        grafo[j][i] = 1;
    }

    /* Adiciona algumas arestas. */
    for (int i = 0; i < n; i++) {
        for (int j = i + 2; j < n; j++) {
            if ((i + j) % 3 == 0 && j != n - 1) {
                grafo[i][j] = 1;
                grafo[j][i] = 1;
            }
        }
    }
}

int main(void) {
    int n = 6;

    char vertices[] = {'A', 'B', 'C', 'D', 'E', 'F'};

    int grafo[MAX][MAX] = {0};

    /* Grafo original. */
    grafo[0][1] = grafo[1][0] = 1;
    grafo[1][3] = grafo[3][1] = 1;
    grafo[1][4] = grafo[4][1] = 1;
    grafo[2][3] = grafo[3][2] = 1;
    grafo[2][4] = grafo[4][2] = 1;
    grafo[3][4] = grafo[4][3] = 1;
    grafo[3][5] = grafo[5][3] = 1;
    grafo[1][2] = grafo[2][1] = 1;
    grafo[0][2] = grafo[2][0] = 1;
    grafo[4][5] = grafo[5][4] = 1;

    int caminho[MAX];
    int visitado[MAX] = {0};

    printf("\n======= CAMINHO HAMILTONIANO =======\n");

    if (encontrar_caminho_hamiltoniano_bt(
        n, grafo, caminho, visitado, 0)) {

        for (int i = 0; i < n; i++) {
            printf("%c ", vertices[caminho[i]]);
        }

        printf("\n");
    } else {
        printf("Nao existe caminho hamiltoniano.\n");
    }

    /* Reducao para TSP. */
    int pesos[MAX][MAX];

    grafo_para_tsp(n, grafo, pesos);

    int melhor[MAX];
    int guloso[MAX];
    int insercao[MAX];

    printf("\n======= TSP FORCA BRUTA =======\n");

    int custo = tsp_forca_bruta(n, pesos, melhor);

    imprimir_caminho(n, melhor);
    printf("Custo: %d\n", custo);

    printf("\n======= VIZINHO MAIS PROXIMO =======\n");

    custo = tsp_vizinho_mais_proximo(n, pesos, guloso);

    imprimir_caminho(n, guloso);
    printf("Custo: %d\n", custo);

    printf("\n======= INSERCAO DO MAIS PROXIMO =======\n");

    custo = tsp_insercao(n, pesos, insercao);

    imprimir_caminho(n, insercao);
    printf("Custo: %d\n", custo);

    /* Experimento. */
    int tamanhos[] = {5, 8, 10, 12};

    printf("\n======= EXPERIMENTO =======\n");
    printf("N\tForca Bruta\tVizinho Prox.\tInsercao\n");

    for (int k = 0; k < 4; k++) {
        n = tamanhos[k];

        int g[MAX][MAX] = {0};
        int p[MAX][MAX];

        int caminho_bt[MAX];
        int caminho_guloso[MAX];
        int caminho_insercao[MAX];

        gerar_grafo(n, g);
        grafo_para_tsp(n, g, p);

        clock_t inicio = clock();

        int custo_bt = tsp_forca_bruta(n, p, caminho_bt);

        clock_t fim = clock();
        double tempo_bt = (double)(fim - inicio) / CLOCKS_PER_SEC;

        inicio = clock();

        int custo_guloso = tsp_vizinho_mais_proximo(n, p, caminho_guloso);

        fim = clock();
        double tempo_guloso = (double)(fim - inicio) / CLOCKS_PER_SEC;

        inicio = clock();

        int custo_insercao = tsp_insercao(n, p, caminho_insercao);

        fim = clock();
        double tempo_insercao = (double)(fim - inicio) / CLOCKS_PER_SEC;

        printf("%d\t%.6f (%d)\t%.6f (%d)\t%.6f (%d)\n",n,tempo_bt, custo_bt, tempo_guloso, custo_guloso, tempo_insercao, custo_insercao);
    }

    return 0;
}
