
#include <stdio.h>
#include "agm.h"

int main(void) {
    int V = 6;
    int E = 10;

    char vertices[] = {'A', 'B', 'C', 'D', 'E', 'F'};

    Aresta arestas[] = {
        {0, 1, 4},  /* A -- B */
        {1, 3, 5},  /* B -- D */
        {1, 4, 8},  /* B -- E */
        {2, 3, 4},  /* C -- D */
        {2, 4, 10}, /* C -- E */
        {3, 4, 2},  /* D -- E */
        {3, 5, 1},  /* D -- F */
        {1, 2, 1},  /* B -- C */
        {0, 2, 2},  /* A -- C */
        {4, 5, 3}   /* E -- F */
    };

    Aresta resultado[V - 1];
    int qtd;
    int peso_total;

    printf("=== KRUSKAL ===\n");

    qtd = kruskal(V, arestas, E, resultado);
    peso_total = 0;

    for (int i = 0; i < qtd; i++) {
        printf("%c -- %c (peso %d)\n",
               vertices[resultado[i].u],
               vertices[resultado[i].v],
               resultado[i].peso);

        peso_total += resultado[i].peso;
    }

    printf("Peso total: %d\n\n", peso_total);

    printf("=== PRIM ===\n");

    qtd = prim(V, arestas, E, resultado);
    peso_total = 0;

    for (int i = 0; i < qtd; i++) {
        printf("%c -- %c (peso %d)\n",
               vertices[resultado[i].u],
               vertices[resultado[i].v],
               resultado[i].peso);

        peso_total += resultado[i].peso;
    }

    printf("Peso total: %d\n", peso_total);

    return 0;
}
