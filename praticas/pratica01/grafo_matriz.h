#ifndef GRAFO_MATRIZ_H
#define GRAFO_MATRIZ_H

// Matriz de adjacência
typedef struct {
    int n;
    int **adj;
} GrafoMatriz;

GrafoMatriz *criar_grafo_matriz(int n);
void inserir_aresta(GrafoMatriz *matriz, int u, int v);
void remover_aresta(GrafoMatriz *matriz, int u, int v);
int grau_matriz(GrafoMatriz *matriz);
int sao_adjacentes_matriz(GrafoMatriz *matriz);
void liberar_grafo(GrafoMatriz *matriz);
void exibir_matriz(GrafoMatriz *matriz);
#endif