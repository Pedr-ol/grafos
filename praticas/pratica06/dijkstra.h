
#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#define MAX_VERTICES 100
#define INFINITO 999999

typedef struct No {
    int vertice;
    int peso;
    struct No *proximo;
} No;

typedef struct {
    No **lista;
    int num_vertices;
} GrafoListaPonderada;

typedef struct {
    int vertice;
    int distancia;
} NoHeap;

typedef struct {
    NoHeap *dados;
    int capacidade, tamanho;
    int *posicao; // Mapeia vértice -> índice no heap
} MinHeap;

GrafoListaPonderada *criar_grafo(int vertices_grafico);
void dijkstra(GrafoListaPonderada *g, int origem, int *dist, int *predecessores);
MinHeap *criar_min_heap(int capacidade);
NoHeap extrair_minimo(MinHeap *heap);
void diminuir_chave(MinHeap *heap, int vertice, int nova_distancia);
void reconstruir_caminho(int origem, int destino, int *predecessores);

#endif
