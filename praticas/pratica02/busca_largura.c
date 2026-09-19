#include <stdlib.h>
#include "busca_largura.h"

static Fila criar_fila(int capacidade) {
    return (Fila){ .dados = malloc(capacidade * sizeof(int)), .capacidade = capacidade, .inicio = 0, .fim = 0, .tamanho = 0 };
}

void bfs(GrafoLista *g, int origem, int *dist, int *pred) {
    int *visitado = calloc(g->n, sizeof(int));
    Fila f = criar_fila(g->n);

    for (int i = 0; i < g->n; i++) dist[i] = pred[i] = -1;

    visitado[origem] = 1;
    dist[origem] = 0;
    f.dados[f.fim++] = origem;
    f.tamanho++;

    while (f.tamanho > 0) {
        int u = f.dados[f.inicio++];
        f.tamanho--;

        for (No *p = g->adj[u]; p; p = p->prox) {
            int v = p->destino;
            if (!visitado[v]) {
                visitado[v] = 1;
                dist[v] = dist[u] + 1;
                pred[v] = u;
                f.dados[f.fim++] = v;
                f.tamanho++;
            }
        }
    }

    free(visitado);
    free(f.dados);
}

int eh_bipartido(GrafoLista *g) {
    int *grupo = malloc(g->n * sizeof(int));
    for (int i = 0; i < g->n; i++) grupo[i] = -1;

    for (int inicio = 0; inicio < g->n; inicio++) {
        if (grupo[inicio] != -1) continue;

        Fila f = criar_fila(g->n);
        grupo[inicio] = 0;
        f.dados[f.fim++] = inicio;
        f.tamanho++;

        while (f.tamanho > 0) {
            int u = f.dados[f.inicio++];
            f.tamanho--;

            for (No *p = g->adj[u]; p; p = p->prox) {
                int v = p->destino;
                if (grupo[v] == -1) {
                    grupo[v] = 1 - grupo[u];
                    f.dados[f.fim++] = v;
                    f.tamanho++;
                } else if (grupo[v] == grupo[u]) {
                    free(grupo);
                    free(f.dados);
                    return 0;
                }
            }
        }
        free(f.dados);
    }

    free(grupo);
    return 1;
}