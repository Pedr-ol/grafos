#include <stdio.h>
#include <stdlib.h>
#include "conectividade.h"
#include "planaridade.h"

// Insere uma aresta não direcionada entre u e v
static void adicionar_aresta(GrafoLista *g, int u, int v) {
    No *p1 = malloc(sizeof(No));
    p1->destino = v;
    p1->prox = g->adj[u];
    g->adj[u] = p1;

    No *p2 = malloc(sizeof(No));
    p2->destino = u;
    p2->prox = g->adj[v];
    g->adj[v] = p2;
}

// Libera a memória alocada para o grafo
static void liberar_grafo(GrafoLista *g) {
    for (int i = 0; i < g->n; i++) {
        No *atual = g->adj[i];
        while (atual) {
            No *temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
    free(g->adj);
}

int main() {
    // -------------------------------------------------------------
    // GRAFO 1: Satisfaz a condição de Euler (Árvore/Caminho 0-1-2-3-4)
    // Vertices (n) = 5, Arestas (m) = 4
    // -------------------------------------------------------------
    printf("\n=== GRAFO 1 (Satisfaz Euler) ===\n");
    GrafoLista g1 = { .n = 5, .m = 4 };
    g1.adj = calloc(g1.n, sizeof(No *));

    adicionar_aresta(&g1, 0, 1);
    adicionar_aresta(&g1, 1, 2);
    adicionar_aresta(&g1, 2, 3);
    adicionar_aresta(&g1, 3, 4);

    detectar_pontes(&g1);

    if (eh_planar_euler(&g1)) {
        printf("Resultado: O grafo satisfaz a condicao de Euler (m <= 3n - 6).\n");
    } else {
        printf("Resultado: O grafo NAO satisfaz a condicao de Euler.\n");
    }

    liberar_grafo(&g1);

    printf("\n-----------------------------------\n\n");

    // -------------------------------------------------------------
    // GRAFO 2: NAO satisfaz a condição de Euler (Grafo Completo K5)
    // Vertices (n) = 5, Arestas (m) = 10
    // Para n = 5, o limite de arestas eh: 3(5) - 6 = 9 arestas.
    // Como m = 10 (10 > 9), ele viola a condição.
    // -------------------------------------------------------------
    printf("=== GRAFO 2 (NAO Satisfaz Euler - K5) ===\n");
    GrafoLista g2 = { .n = 5, .m = 10 };
    g2.adj = calloc(g2.n, sizeof(No *));

    // Conecta todos os pares de vértices (0 a 4)
    for (int i = 0; i < g2.n; i++) {
        for (int j = i + 1; j < g2.n; j++) {
            adicionar_aresta(&g2, i, j);
        }
    }

    detectar_pontes(&g2);

    if (eh_planar_euler(&g2)) {
        printf("Resultado: O grafo satisfaz a condicao de Euler.\n");
    } else {
        printf("Resultado: O grafo NAO satisfaz a condicao de Euler (m > 3n - 6).\n");
    }

    liberar_grafo(&g2);

    return 0;
}