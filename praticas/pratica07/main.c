#include <stdio.h>
#include "bellman_ford.h"

int main(void) {
    int n = 6;

    char vertices[] = {'A', 'B', 'C', 'D', 'E', 'F'};

    GrafoListaPonderado *g = criar_grafo(n);

    adicionar_aresta(g, 0, 1, 4);  /* A -- B */
    adicionar_aresta(g, 1, 3, 5);  /* B -- D */
    adicionar_aresta(g, 1, 4, 8);  /* B -- E */
    adicionar_aresta(g, 2, 3, 4);  /* C -- D */
    adicionar_aresta(g, 2, 4, 10); /* C -- E */
    adicionar_aresta(g, 3, 4, 2);  /* D -- E */
    adicionar_aresta(g, 3, 5, 1);  /* D -- F */
    adicionar_aresta(g, 1, 2, 1);  /* B -- C */
    adicionar_aresta(g, 0, 2, 2);  /* A -- C */
    adicionar_aresta(g, 4, 5, 3);  /* E -- F */

    int dist[6];
    int pred[6];
    int origem = 0;

    if (bellman_ford(g, origem, dist, pred)) {
        printf("\nNao existe ciclo negativo.\n");
        printf("Distancias a partir de %c:\n", vertices[origem]);

        for (int i = 0; i < n; i++) {
            printf("%c: %d\n", vertices[i], dist[i]);
        }
    } else {
        printf("Foi detectado um ciclo negativo!\n");
    }

    destruir_grafo(g);

    return 0;
}
