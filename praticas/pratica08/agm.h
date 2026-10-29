#ifndef AGM_H
#define AGM_H

typedef struct {
    int *pai, *rank;
    int n;
} DSU;

typedef struct {
    int u, v, peso;
} Aresta;

typedef struct No {
    int vertice;
    int peso;
    struct No *prox;
} No;

int find(DSU *d, int x);
void unir(DSU *d, int x, int y);

int kruskal(int V, Aresta arestas[], int E, Aresta resultado[]);
int prim(int V, Aresta arestas[], int E, Aresta resultado[]);

#endif
