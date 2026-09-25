#ifndef COLORACAO_H
#define COLORACAO_H

// Lista de Adjacência
typedef struct No {
    int vertice;
    struct No *prox;
} No;

typedef struct GrafoLista {
    int num_vertices;
    No **lista_adj;
} GrafoLista;


int* coloracao_gulosa(GrafoLista *g, int *num_cores);
int* coloracao_welsh_powell(GrafoLista *g, int *num_cores);
int eh_bipartido(GrafoLista *g);
GrafoLista* criar_grafo(int num_vertices);
void adicionar_aresta(GrafoLista *g, int u, int v);
void destruir_grafo(GrafoLista *g);

#endif