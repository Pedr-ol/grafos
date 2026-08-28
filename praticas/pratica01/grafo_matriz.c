#include <stdio.h>
#include <stdlib.h>
#include "grafo_matriz.h"

GrafoMatriz *criar_grafo_matriz(int n)
{
    if (n <= 0){
        return NULL;
    }
    GrafoMatriz *matriz = malloc(sizeof(GrafoMatriz));
    if (matriz == NULL)
        return NULL;

    matriz->n = n;

    matriz->adj = malloc(n * sizeof(int *));

    if (matriz->adj == NULL)
    {
        free(matriz);
        return NULL;
    }

    for (int i = 0; i < n; i++)
    {
        matriz->adj[i] = malloc(n * sizeof(int));

        if(matriz->adj[i] == NULL) {
            for (int j = 0; j<i; j++)
                free(matriz->adj[j]);
            free(matriz->adj);
            free(matriz);

            return NULL;
        }
        for (int j = 0; j < n; j++)
            matriz->adj[i][j] = 0;
            
    }
    return matriz;
}

void inserir_aresta(GrafoMatriz *matriz, int u, int v)
{
    matriz->adj[u][v] = 1;
    matriz->adj[v][u] = 1;
}

void remover_aresta(GrafoMatriz *matriz, int u, int v) 
{
    matriz->adj[u][v] = 0;
    matriz->adj[v][u] = 0;
}

void exibir_matriz(GrafoMatriz *matriz)
{
    for (int i = 0; i < matriz->n; i++)
    {
        for (int j = 0; j < matriz->n; j++)
        {
            printf("%d ", matriz->adj[i][j]);
        }
        printf("\n");
    }
}

// int grau_matriz(GrafoMatriz *matriz) {}
// int sao_adjacentes_matriz(GrafoMatriz *matriz) {}
// void liberar_grafo(GrafoMatriz *matriz) {}