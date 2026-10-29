
#ifndef BELLMAN_FORD_H
#define BELLMAN_FORD_H

typedef struct No {
    int vertice;
    int peso;
    struct No *proximo;
} No;

typedef struct {
    No **lista;
    int num_vertices;
} GrafoListaPonderado;

GrafoListaPonderado *criar_grafo(int n);
void adicionar_aresta(GrafoListaPonderado *g, int u, int v, int peso);
void destruir_grafo(GrafoListaPonderado *g);

int bellman_ford(GrafoListaPonderado *g, int origem, int *dist, int *pred);
void reconstruir_ciclo_negativo(int n, int *pred, int vertice);

#endif
