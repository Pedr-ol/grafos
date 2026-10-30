#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cobertura.h"

void imprimir_resultado(char *nome, int *selecionados, int n, int tamanho, double tempo) {
    printf("%s\n", nome);

    printf("Vertices selecionados: ");

    for (int i = 0; i < n; i++) {
        if (selecionados[i]) {
            printf("%d ", i);
        }
    }

    printf("\nQuantidade: %d", tamanho);
    printf("\nTempo: %.6f segundos\n\n", tempo);
}

int main(void) {
    /* Grafo original */
    Grafo *g = criar_grafo(6);

    adicionar_aresta(g, 0, 1); 
    adicionar_aresta(g, 1, 3); 
    adicionar_aresta(g, 1, 4); 
    adicionar_aresta(g, 2, 3); 
    adicionar_aresta(g, 2, 4); 
    adicionar_aresta(g, 3, 4); 
    adicionar_aresta(g, 3, 5); 
    adicionar_aresta(g, 1, 2); 
    adicionar_aresta(g, 0, 2); 
    adicionar_aresta(g, 4, 5); 

    int melhor[6] = {0};
    int gulosa[6] = {0};

    int tamanho_bt;
    int tamanho_guloso;

    clock_t inicio = clock();

    cobertura_minima_bt(g, melhor, &tamanho_bt);

    clock_t fim = clock();

    double tempo_bt = (double)(fim - inicio) / CLOCKS_PER_SEC;

    inicio = clock();

    cobertura_gulosa(g, gulosa, &tamanho_guloso);

    fim = clock();

    double tempo_guloso = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("\n=== GRAFO ORIGINAL ===\n\n");

    imprimir_resultado("BACKTRACKING", melhor, 6, tamanho_bt, tempo_bt);

    imprimir_resultado("GULOSO", gulosa, 6, tamanho_guloso, tempo_guloso);

    destruir_grafo(g);

    /* Experimento com diferentes tamanhos. */
    int tamanhos[] = {5, 8, 10, 12, 15};

    printf("======= EXPERIMENTO =======\n\n");
    printf("N\tBT (s)\t\tGuloso (s)\n");

    for (int k = 0; k < 5; k++) {
        int n = tamanhos[k];

        Grafo *teste = criar_grafo(n);

        /* Gera um grafo completo para o teste. */
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                adicionar_aresta(teste, i, j);
            }
        }

        int *bt = calloc(n, sizeof(int));
        int *gr = calloc(n, sizeof(int));

        inicio = clock();

        cobertura_minima_bt(teste, bt, &tamanho_bt);

        fim = clock();

        tempo_bt = (double)(fim - inicio) / CLOCKS_PER_SEC;

        inicio = clock();

        cobertura_gulosa(teste, gr, &tamanho_guloso);

        fim = clock();

        tempo_guloso = (double)(fim - inicio) / CLOCKS_PER_SEC;

        printf("%d\t%.6f\t%.6f\n",
               n, tempo_bt, tempo_guloso);

        free(bt);
        free(gr);
        destruir_grafo(teste);
    }

    return 0;
}
