#include <stdio.h>
#include <stdlib.h>
#include "coloracao.h"

int main() {
    int num_vertices = 5;
    GrafoLista *g = criar_grafo(num_vertices);

    // Grafo Exemplo (Ciclo de 5 vértices: C5)
    adicionar_aresta(g, 0, 1);
    adicionar_aresta(g, 1, 2);
    adicionar_aresta(g, 2, 3);
    adicionar_aresta(g, 3, 4);
    adicionar_aresta(g, 4, 0);

    int total_cores = 0;

    // Teste 1: Coloração Gulosa
    int *cores_gulosa = coloracao_gulosa(g, &total_cores);
    printf("\n--- Coloração Gulosa ---\nTotal de cores: %d\n", total_cores);
    for (int i = 0; i < num_vertices; i++) {
        printf("    Vértice %d -> Cor %d\n", i, cores_gulosa[i]);
    }
    free(cores_gulosa);

    // Teste 2: Welsh-Powell
    int *cores_wp = coloracao_welsh_powell(g, &total_cores);
    printf("\n--- Coloração Welsh-Powell ---\nTotal de cores: %d\n", total_cores);
    for (int i = 0; i < num_vertices; i++) {
        printf("    Vértice %d -> Cor %d\n", i, cores_wp[i]);
    }
    free(cores_wp);

    // Teste 3: Bipartido
    printf("\n--- Teste de Bipartição ---\n");
    if (eh_bipartido(g)) {
        printf("O grafo é Bipartido (Número cromático <= 2).\n");
    } else {
        printf("O grafo NÃO é Bipartido.\n");
    }

    destruir_grafo(g);
    return 0;
}