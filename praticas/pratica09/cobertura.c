#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cobertura.h"

Grafo *criar_grafo(int n) {
    Grafo *g = malloc(sizeof(Grafo));

    g->n = n;
    g->matriz = malloc(n * sizeof(int *));

    for (int i = 0; i < n; i++) {
        g->matriz[i] = calloc(n, sizeof(int));
    }

    return g;
}

void adicionar_aresta(Grafo *g, int u, int v) {
    g->matriz[u][v] = 1;
    g->matriz[v][u] = 1;
}

void destruir_grafo(Grafo *g) {
    for (int i = 0; i < g->n; i++) {
        free(g->matriz[i]);
    }

    free(g->matriz);
    free(g);
}

/* Verifica se todas as arestas estão cobertas. */
int eh_cobertura(Grafo *g, int *selecionados) {
    for (int u = 0; u < g->n; u++) {
        for (int v = u + 1; v < g->n; v++) {
            if (g->matriz[u][v] == 1 &&
                selecionados[u] == 0 &&
                selecionados[v] == 0) {
                return 0;
            }
        }
    }

    return 1;
}

/* BACKTRACKING */

void buscar(Grafo *g, int *selecionados,
            int *melhor, int *tamanho_atual,
            int *melhor_tamanho, int pos) {

    if (*tamanho_atual >= *melhor_tamanho) {
        return;
    }

    if (eh_cobertura(g, selecionados)) {
        *melhor_tamanho = *tamanho_atual;

        for (int i = 0; i < g->n; i++) {
            melhor[i] = selecionados[i];
        }

        return;
    }

    if (pos == g->n) {
        return;
    }

    /* Seleciona o vértice atual. */
    selecionados[pos] = 1;
    (*tamanho_atual)++;

    buscar(g, selecionados, melhor, tamanho_atual,
           melhor_tamanho, pos + 1);

    /* Não seleciona o vértice atual. */
    selecionados[pos] = 0;
    (*tamanho_atual)--;

    buscar(g, selecionados, melhor, tamanho_atual,
           melhor_tamanho, pos + 1);
}

void cobertura_minima_bt(Grafo *g, int *melhor, int *tamanho) {
    int *selecionados = calloc(g->n, sizeof(int));
    int tamanho_atual = 0;

    *tamanho = g->n + 1;

    buscar(g, selecionados, melhor, &tamanho_atual,
           tamanho, 0);

    free(selecionados);
}

/* GULOSO */

void cobertura_gulosa(Grafo *g, int *selecionados, int *tamanho) {
    int *cobertas = calloc(g->n, sizeof(int));

    *tamanho = 0;

    for (int i = 0; i < g->n; i++) {
        selecionados[i] = 0;
    }

    while (!eh_cobertura(g, selecionados)) {
        int maior_grau = -1;
        int escolhido = -1;

        for (int i = 0; i < g->n; i++) {
            if (selecionados[i]) {
                continue;
            }

            int grau = 0;

            for (int j = 0; j < g->n; j++) {
                if (g->matriz[i][j] && !selecionados[j]) {
                    grau++;
                }
            }

            if (grau > maior_grau) {
                maior_grau = grau;
                escolhido = i;
            }
        }

        if (escolhido == -1 || maior_grau == 0) {
            break;
        }

        selecionados[escolhido] = 1;
        (*tamanho)++;
    }

    free(cobertas);
}
