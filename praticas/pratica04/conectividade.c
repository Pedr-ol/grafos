#include <stdio.h>
#include "conectividade.h"

// Retorna o menor valor entre dois inteiros
static inline int min(int a, int b) {
    return (a < b) ? a : b;
}

void dfs_articulacoes(GrafoLista *g, int u, int *descoberta, int *low, 
                      int *pai, int *tempo, int *articulacao) {
    descoberta[u] = low[u] = ++(*tempo);
    
    int filhos = 0;

    for (No *p = g->adj[u]; p != NULL; p = p->prox) {
        int v = p->destino;

        if (descoberta[v] == -1) { // Vértice não visitado
            pai[v] = u;
            filhos++;

            dfs_articulacoes(g, v, descoberta, low, pai, tempo, articulacao);

            low[u] = min(low[u], low[v]);

            // Regras de identificação do ponto de articulação
            if (pai[u] == -1 && filhos > 1) articulacao[u] = 1;
            if (pai[u] != -1 && low[v] >= descoberta[u]) articulacao[u] = 1;
        } 
        else if (v != pai[u]) { // Aresta de retorno
            low[u] = min(low[u], descoberta[v]);
        }
    }
}

void detectar_pontes(GrafoLista *g) {
    int descoberta[g->n], low[g->n], pai[g->n], articulacao[g->n];
    int tempo = 0;

    // Inicialização
    for (int i = 0; i < g->n; i++) {
        descoberta[i] = pai[i] = -1;
        articulacao[i] = 0;
    }

    // Executa a DFS para componentes conexas
    for (int i = 0; i < g->n; i++) {
        if (descoberta[i] == -1) {
            dfs_articulacoes(g, i, descoberta, low, pai, &tempo, articulacao);
        }
    }

    // Exibe as Pontes encontradas
    printf("Pontes:\n");
    for (int u = 0; u < g->n; u++) {
        for (No *p = g->adj[u]; p != NULL; p = p->prox) {
            int v = p->destino;
            if (pai[v] == u && low[v] > descoberta[u]) {
                printf("%d - %d\n", u, v);
            }
        }
    }

    // Exibe os Articulações encontradas
    printf("Articulacoes:\n");
    for (int i = 0; i < g->n; i++) {
        if (articulacao[i]) printf("%d ", i);
    }
    printf("\n");
}