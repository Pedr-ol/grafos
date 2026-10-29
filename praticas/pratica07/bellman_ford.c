
#include <stdio.h>
#include <stdlib.h>
#include "bellman_ford.h"

#define INFINITO 999999

GrafoListaPonderado *criar_grafo(int n) {
    GrafoListaPonderado *g = malloc(sizeof(GrafoListaPonderado));

    g->num_vertices = n;
    g->lista = calloc(n, sizeof(No *));

    return g;
}

void adicionar_aresta(GrafoListaPonderado *g, int u, int v, int peso) {
    No *novo = malloc(sizeof(No));

    novo->vertice = v;
    novo->peso = peso;
    novo->proximo = g->lista[u];
    g->lista[u] = novo;

    /* O grafo é não direcionado. */
    novo = malloc(sizeof(No));

    novo->vertice = u;
    novo->peso = peso;
    novo->proximo = g->lista[v];
    g->lista[v] = novo;
}

void destruir_grafo(GrafoListaPonderado *g) {
    for (int i = 0; i < g->num_vertices; i++) {
        No *atual = g->lista[i];

        while (atual != NULL) {
            No *temp = atual;
            atual = atual->proximo;
            free(temp);
        }
    }

    free(g->lista);
    free(g);
}

int bellman_ford(GrafoListaPonderado *g, int origem,
                 int *dist, int *pred) {
    int n = g->num_vertices;

    for (int i = 0; i < n; i++) {
        dist[i] = INFINITO;
        pred[i] = -1;
    }

    dist[origem] = 0;

    /* Relaxamento das arestas: V - 1 vezes. */
    for (int i = 0; i < n - 1; i++) {
        int alterou = 0;

        for (int u = 0; u < n; u++) {
            if (dist[u] == INFINITO) {
                continue;
            }

            No *atual = g->lista[u];

            while (atual != NULL) {
                int v = atual->vertice;
                int peso = atual->peso;

                if (dist[u] + peso < dist[v]) {
                    dist[v] = dist[u] + peso;
                    pred[v] = u;
                    alterou = 1;
                }

                atual = atual->proximo;
            }
        }

        if (!alterou) {
            break;
        }
    }

    /* Verifica se ainda existe relaxamento possível. */
    for (int u = 0; u < n; u++) {
        if (dist[u] == INFINITO) {
            continue;
        }

        No *atual = g->lista[u];

        while (atual != NULL) {
            int v = atual->vertice;
            int peso = atual->peso;

            if (dist[u] + peso < dist[v]) {
                pred[v] = u;

                reconstruir_ciclo_negativo(n, pred, v);
                return 0;
            }

            atual = atual->proximo;
        }
    }

    return 1;
}

void reconstruir_ciclo_negativo(int n, int *pred, int vertice) {
    int atual = vertice;

    /* Retrocede n vezes para entrar no ciclo. */
    for (int i = 0; i < n; i++) {
        if (atual == -1) {
            printf("Nao foi possivel reconstruir o ciclo.\n");
            return;
        }

        atual = pred[atual];
    }

    if (atual == -1) {
        printf("Nao foi possivel reconstruir o ciclo.\n");
        return;
    }

    int inicio = atual;

    printf("Ciclo negativo: %d", inicio);
    atual = pred[inicio];

    while (atual != inicio && atual != -1) {
        printf(" <- %d", atual);
        atual = pred[atual];
    }

    if (atual == inicio) {
        printf(" <- %d", inicio);
    }

    printf("\n");
}
