#include <stdlib.h>
#include "busca_profundidade.h"

void dfs_recursiva(GrafoLista *g, int u, int *visitado) {
    visitado[u] = 1;

    for (No *p = g->adj[u]; p; p = p->prox) {
        if (!visitado[p->destino]) {
            dfs_recursiva(g, p->destino, visitado);
        }
    }
}

int contar_componentes(GrafoLista *g) {
    int *visitado = calloc(g->n, sizeof(int));
    int componentes = 0;

    for (int i = 0; i < g->n; i++) {
        if (!visitado[i]) {
            componentes++;
            dfs_recursiva(g, i, visitado);
        }
    }

    free(visitado);
    return componentes;
}

int verificar_ciclo(GrafoLista *g, int u, int pai, int *visitado) {
    visitado[u] = 1;

    for (No *p = g->adj[u]; p; p = p->prox) {
        int v = p->destino;
        if (!visitado[v]) {
            if (verificar_ciclo(g, v, u, visitado)) return 1;
        } else if (v != pai) {
            return 1;
        }
    }

    return 0;
}

int tem_ciclo(GrafoLista *g) {
    int *visitado = calloc(g->n, sizeof(int));

    for (int i = 0; i < g->n; i++) {
        if (!visitado[i] && verificar_ciclo(g, i, -1, visitado)) {
            free(visitado);
            return 1;
        }
    }

    free(visitado);
    return 0;
}