#include <stdlib.h>
#include "dag.h"

GrafoLista* criar_grafo(int n) {
    GrafoLista* g = malloc(sizeof(GrafoLista));
    g->num_vertices = n;
    g->listas = calloc(n, sizeof(No*));
    return g;
}

void adicionar_aresta(GrafoLista* g, int u, int v) {
    No* novo = malloc(sizeof(No));
    novo->vertice = v;
    novo->prox = g->listas[u];
    g->listas[u] = novo;
}

// DFS Auxiliar (0: nao visitado, 1: em progresso, 2: concluido)
static int dfs(GrafoLista *g, int u, int *cor, int *res, int *pos) {
    cor[u] = 1;
    for (No* p = g->listas[u]; p; p = p->prox) {
        if (cor[p->vertice] == 1) return 1; // Ciclo!
        if (cor[p->vertice] == 0 && dfs(g, p->vertice, cor, res, pos)) return 1;
    }
    cor[u] = 2;
    res[(*pos)--] = u;
    return 0;
}

int* ordenacao_topologica_dfs(GrafoLista *g, int *tamanho) {
    int n = g->num_vertices;
    int *cor = calloc(n, sizeof(int));
    int *res = malloc(n * sizeof(int));
    int pos = n - 1;

    for (int i = 0; i < n; i++) {
        if (cor[i] == 0 && dfs(g, i, cor, res, &pos)) {
            free(cor);
            free(res);
            *tamanho = 0;
            return NULL;
        }
    }
    free(cor);
    *tamanho = n;
    return res;
}

int* ordenacao_topologica_kahn(GrafoLista *g, int *tamanho) {
    int n = g->num_vertices;
    int *grau = calloc(n, sizeof(int));
    int *res = malloc(n * sizeof(int));
    int ini = 0, fim = 0;

    for (int u = 0; u < n; u++)
        for (No* p = g->listas[u]; p; p = p->prox)
            grau[p->vertice]++;

    for (int i = 0; i < n; i++)
        if (grau[i] == 0) res[fim++] = i;

    while (ini < fim) {
        int u = res[ini++];
        for (No* p = g->listas[u]; p; p = p->prox)
            if (--grau[p->vertice] == 0) res[fim++] = p->vertice;
    }

    free(grau);

    if (fim < n) {
        free(res);
        *tamanho = 0;
        return NULL;
    }

    *tamanho = fim;
    return res;
}

int eh_dag(GrafoLista *g) {
    int tam;
    int *res = ordenacao_topologica_dfs(g, &tam);
    if (res) {
        free(res);
        return 1;
    }
    return 0;
}