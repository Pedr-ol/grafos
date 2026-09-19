
#ifndef CONECTIVIDADE_H
#define CONECTIVIDADE_H

typedef struct No {
    int destino;
    struct No *prox;
} No;

typedef struct {
    int n;
    int m;
    No **adj;
} GrafoLista;

void dfs_articulacoes(GrafoLista *g, int u, int *descoberta,
                      int *low, int *pai, int *tempo,
                      int *articulacao);

void detectar_pontes(GrafoLista *g);

#endif