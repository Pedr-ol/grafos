
#include <stdio.h>
#include <stdlib.h>
#include "dijkstra.h"

/* Adiciona uma aresta direcionada ao grafo */
void adicionar_aresta(GrafoListaPonderada *g, int origem, int destino, int peso)
{
    No *novo = malloc(sizeof(No));

    if (novo == NULL)
    {
        return;
    }

    novo->vertice = destino;
    novo->peso = peso;
    novo->proximo = g->lista[origem];

    g->lista[origem] = novo;
}

/* Libera a memória do grafo */
void liberar_grafo(GrafoListaPonderada *g)
{
    if (g == NULL)
    {
        return;
    }

    for (int i = 0; i < g->num_vertices; i++)
    {
        No *atual = g->lista[i];

        while (atual != NULL)
        {
            No *temp = atual;
            atual = atual->proximo;
            free(temp);
        }
    }

    free(g->lista);
    free(g);
}

int main(void)
{
    int vertices_grafico = 6;
    int dist[MAX_VERTICES];
    int predecessores[MAX_VERTICES];
    int origem, destino;

    GrafoListaPonderada *g = criar_grafo(vertices_grafico);

    if (g == NULL)
    {
        printf("Erro ao criar o grafo.\n");
        return 1;
    }
    // 0=A, 1=B, 2=C, 3=D, 4=E, 5=F
    /* Adiciona as arestas do grafo */
    adicionar_aresta(g, 0, 1, 4);
    adicionar_aresta(g, 0, 2, 2);
    adicionar_aresta(g, 1, 2, 1);
    adicionar_aresta(g, 1, 4, 8);
    adicionar_aresta(g, 1, 3, 5);
    adicionar_aresta(g, 2, 3, 4);
    adicionar_aresta(g, 2, 4, 10);
    adicionar_aresta(g, 3, 4, 2);
    adicionar_aresta(g, 3, 5, 1);
    adicionar_aresta(g, 4, 5, 3);
    adicionar_aresta(g, 4, 5, 3);
    adicionar_aresta(g, 1, 0, 4);
    adicionar_aresta(g, 2, 0, 2);
    adicionar_aresta(g, 2, 1, 1);
    adicionar_aresta(g, 4, 1, 8);
    adicionar_aresta(g, 3, 1, 5);
    adicionar_aresta(g, 3, 2, 4);
    adicionar_aresta(g, 4, 2, 10);
    adicionar_aresta(g, 4, 3, 2);
    adicionar_aresta(g, 5, 3, 1);
    adicionar_aresta(g, 5, 4, 3);
    adicionar_aresta(g, 5, 4, 3);

    // 0=A, 1=B, 2=C, 3=D, 4=E, 5=F
    printf("Vertices: 0, 1, 2, 3, 4, 5\n");

    printf("Digite o vertice de origem: ");
    if (scanf("%d", &origem) != 1 || origem < 0 || origem >= vertices_grafico)
    {
        printf("Origem invalida.\n");
        liberar_grafo(g);
        return 1;
    }

    printf("Digite o vertice de destino: ");
    if (scanf("%d", &destino) != 1 ||
        destino < 0 || destino >= vertices_grafico)
    {
        printf("Destino invalido.\n");
        liberar_grafo(g);
        return 1;
    }

    dijkstra(g, origem, dist, predecessores);

    if (dist[destino] == INFINITO)
    {
        printf("Nao existe caminho entre esses vertices.\n");
    }
    else
    {
        printf("\nMenor distancia: %d\n", dist[destino]);
        printf("Caminho: ");
        reconstruir_caminho(origem, destino, predecessores);
    }

    liberar_grafo(g);

    return 0;
}
