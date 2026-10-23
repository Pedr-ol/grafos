#include <stdlib.h>
#include <stdio.h>
#include "dijkstra.h"

GrafoListaPonderada *criar_grafo(int vertices_grafico)
{
    GrafoListaPonderada *g = malloc(sizeof(GrafoListaPonderada));

    if (g == NULL)
    {
        return NULL;
    }

    g->lista = calloc(vertices_grafico, sizeof(No *));

    if (g->lista == NULL)
    {
        free(g);
        return NULL;
    }

    g->num_vertices = vertices_grafico;
    return g;
}

void dijkstra(GrafoListaPonderada *g, int origem, int *dist, int *predecessores)
{
    if (g == NULL || dist == NULL || predecessores == NULL ||
        origem < 0 || origem >= g->num_vertices)
    {
        return;
    }

    int vertices_grafico = g->num_vertices;
    MinHeap *heap = criar_min_heap(vertices_grafico);

    if (heap == NULL)
    {
        return;
    }

    for (int i = 0; i < vertices_grafico; i++)
    {
        dist[i] = INFINITO;
        predecessores[i] = -1;
    }

    dist[origem] = 0;
    diminuir_chave(heap, origem, 0);

    while (heap->tamanho > 0)
    {
        NoHeap atual = extrair_minimo(heap);
        int u = atual.vertice;

        if (dist[u] == INFINITO)
        {
            break;
        }

        No *vizinho = g->lista[u];

        while (vizinho != NULL)
        {
            int v = vizinho->vertice;
            int peso = vizinho->peso;

            if (v >= 0 && v < vertices_grafico && peso >= 0 &&
                heap->posicao[v] != -1 &&
                dist[u] <= INFINITO - peso &&
                dist[u] + peso < dist[v])
            {

                dist[v] = dist[u] + peso;
                predecessores[v] = u;

                diminuir_chave(heap, v, dist[v]);
            }

            vizinho = vizinho->proximo;
        }
    }

    free(heap->dados);
    free(heap->posicao);
    free(heap);
}

MinHeap *criar_min_heap(int capacidade)
{
    MinHeap *heap = malloc(sizeof(MinHeap));

    if (heap == NULL)
    {
        return NULL;
    }

    heap->dados = malloc(capacidade * sizeof(NoHeap));
    heap->posicao = malloc(capacidade * sizeof(int));

    if (heap->dados == NULL || heap->posicao == NULL)
    {
        free(heap->dados);
        free(heap->posicao);
        free(heap);

        return NULL;
    }

    heap->capacidade = capacidade;
    heap->tamanho = capacidade;

    for (int i = 0; i < capacidade; i++)
    {
        heap->dados[i].vertice = i;
        heap->dados[i].distancia = INFINITO;
        heap->posicao[i] = i;
    }

    return heap;
}

void trocar(MinHeap *heap, int i, int j)
{
    NoHeap aux = heap->dados[i];
    heap->dados[i] = heap->dados[j];
    heap->dados[j] = aux;

    heap->posicao[heap->dados[i].vertice] = i;
    heap->posicao[heap->dados[j].vertice] = j;
}

NoHeap extrair_minimo(MinHeap *heap)
{
    NoHeap minimo = heap->dados[0];

    heap->posicao[minimo.vertice] = -1;
    heap->tamanho--;

    if (heap->tamanho > 0)
    {
        heap->dados[0] = heap->dados[heap->tamanho];
        heap->posicao[heap->dados[0].vertice] = 0;

        int i = 0;

        while (2 * i + 1 < heap->tamanho)
        {
            int filho = 2 * i + 1;

            if (filho + 1 < heap->tamanho &&
                heap->dados[filho + 1].distancia <
                    heap->dados[filho].distancia)
            {
                filho++;
            }

            if (heap->dados[i].distancia <=
                heap->dados[filho].distancia)
            {
                break;
            }

            trocar(heap, i, filho);
            i = filho;
        }
    }

    return minimo;
}

void diminuir_chave(MinHeap *heap, int vertice, int nova_distancia)
{
    int i = heap->posicao[vertice];

    if (i < 0 || i >= heap->tamanho)
    {
        return;
    }

    heap->dados[i].distancia = nova_distancia;

    while (i > 0)
    {
        int pai = (i - 1) / 2;

        if (heap->dados[pai].distancia <= heap->dados[i].distancia)
        {
            break;
        }

        trocar(heap, i, pai);
        i = pai;
    }
}

void reconstruir_caminho(int origem, int destino, int *predecessores)
{
    if (predecessores == NULL || origem < 0 || destino < 0)
    {
        return;
    }

    if (origem == destino)
    {
        printf("%d\n", origem);
        return;
    }

    if (predecessores[destino] == -1)
    {
        printf("Esse caminho nao existe\n");
        return;
    }

    reconstruir_caminho(origem, predecessores[destino], predecessores);
    printf(" -> %d", destino);
}