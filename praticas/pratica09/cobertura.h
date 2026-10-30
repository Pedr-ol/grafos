#ifndef COBERTURA_H
#define COBERTURA_H

typedef struct {
    int n;
    int **matriz;
} Grafo;

Grafo *criar_grafo(int n);
void adicionar_aresta(Grafo *g, int u, int v);
void destruir_grafo(Grafo *g);

int eh_cobertura(Grafo *g, int *selecionados);
void cobertura_minima_bt(Grafo *g, int *melhor, int *tamanho);
void cobertura_gulosa(Grafo *g, int *selecionados, int *tamanho);

#endif
