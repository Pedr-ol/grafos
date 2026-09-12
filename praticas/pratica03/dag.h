#ifndef DAG_H
#define DAG_H

typedef struct No {
    int vertice;
    struct No* prox;
} No;

typedef struct {
    int num_vertices;
    No** listas;
} GrafoLista;

GrafoLista* criar_grafo(int n);
void adicionar_aresta(GrafoLista* g, int u, int v);
int* ordenacao_topologica_kahn(GrafoLista *g, int *tamanho);
int* ordenacao_topologica_dfs(GrafoLista *g, int *tamanho);
int eh_dag(GrafoLista *g);

#endif