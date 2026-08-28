#ifndef GRAFO_LISTA_H
#define GRAFO_LISTA_H


// Lista de adjacência
typedef struct No {
    int destino;
    struct No *prox;
} No;

typedef struct {
    int n;
    No **adj;
} GrafoLista;

GrafoLista criar_grafo_lista(int n);
int grau(GrafoLista *lista);
void sao_adjacentes(GrafoLista *lista);

#endif