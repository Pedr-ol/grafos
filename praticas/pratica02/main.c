#include <stdio.h>
#include <stdlib.h>
#include "busca_largura.h"
#include "busca_profundidade.h"

void adicionar_aresta(GrafoLista *g, int u, int v) {
    No *no1 = malloc(sizeof(No));
    *no1 = (No){ .destino = v, .prox = g->adj[u] };
    g->adj[u] = no1;

    No *no2 = malloc(sizeof(No));
    *no2 = (No){ .destino = u, .prox = g->adj[v] };
    g->adj[v] = no2;
}

void liberar_grafo(GrafoLista *g) {
    for (int i = 0; i < g->n; i++) {
        No *p = g->adj[i];
        while (p) {
            No *tmp = p;
            p = p->prox;
            free(tmp);
        }
    }
    free(g->adj);
}

void exemplo_sem_ciclo() {
    printf("=== EXEMPLO 1: Grafo Sem Ciclo (Árvore) ===\n");
    GrafoLista g = { .n = 5, .adj = calloc(5, sizeof(No *)) };

    // Estrutura em árvore: 0-1, 0-2, 1-3, 2-4
    adicionar_aresta(&g, 0, 1);
    adicionar_aresta(&g, 0, 2);
    adicionar_aresta(&g, 1, 3);
    adicionar_aresta(&g, 2, 4);

    int dist[5], pred[5];
    bfs(&g, 0, dist, pred);

    printf("BFS (Distancias a partir do vertice 0):\n");
    for (int i = 0; i < g.n; i++) {
        printf("  Vertice %d: dist = %d, pred = %d\n", i, dist[i], pred[i]);
    }

    printf("Componentes: %d\n", contar_componentes(&g)); 
    printf("Bipartido:   %d\n", eh_bipartido(&g));         
    printf("Tem ciclo:   %d\n", tem_ciclo(&g));             

    liberar_grafo(&g);
}

void exemplo_com_ciclo() {
    printf("\n=== EXEMPLO 2: Grafo Com Ciclo (Triângulo 0-1-2) ===\n");
    GrafoLista g = { .n = 5, .adj = calloc(5, sizeof(No *)) };

    // Mesmas arestas do exemplo 1 + aresta (1-2) que fecha o ciclo
    adicionar_aresta(&g, 0, 1);
    adicionar_aresta(&g, 0, 2);
    adicionar_aresta(&g, 1, 3);
    adicionar_aresta(&g, 2, 4);
    adicionar_aresta(&g, 1, 2); //  Cria o ciclo

    int dist[5], pred[5];
    bfs(&g, 0, dist, pred);

    printf("BFS (Distancias a partir do vertice 0):\n");
    for (int i = 0; i < g.n; i++) {
        printf("  Vertice %d: dist = %d, pred = %d\n", i, dist[i], pred[i]);
    }

    printf("Componentes: %d\n", contar_componentes(&g)); 
    printf("Bipartido:   %d\n", eh_bipartido(&g));        
    printf("Tem ciclo:   %d\n", tem_ciclo(&g));             

    liberar_grafo(&g);
}

int main() {
    exemplo_sem_ciclo();
    exemplo_com_ciclo();
    return 0;
}