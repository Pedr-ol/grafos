#include <stdio.h>
#include <stdlib.h>
#include "coloracao.h"

// Função auxiliar para atribuir cores 
static int* colorir_por_ordem(GrafoLista *g, int *ordem, int *num_cores) {
    int n = g->num_vertices;
    int *cores = (int*) malloc(n * sizeof(int));
    int *disponivel = (int*) malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        cores[i] = -1; // -1 significa sem cor
        disponivel[i] = 1; // 1 = disponível
    }

    cores[ordem[0]] = 0;
    int max_cor = 0;

    // Colorir os vertices
    for (int i = 1; i < n; i++) {
        int u = ordem[i];

        // Cores dos vizinhos já coloridos marcado como indisponíveis
        for (No *p = g->lista_adj[u]; p != NULL; p = p->prox) {
            int v = p->vertice;
            if (cores[v] != -1) {
                disponivel[cores[v]] = 0;
            }
        }

        // Encontrar a menor cor disponível
        int cor;
        for (cor = 0; cor < n; cor++) {
            if (disponivel[cor]) break;
        }

        cores[u] = cor;
        if (cor > max_cor) max_cor = cor;

        for (No *p = g->lista_adj[u]; p != NULL; p = p->prox) {
            int v = p->vertice;
            if (cores[v] != -1) {
                disponivel[cores[v]] = 1;
            }
        }
    }

    free(disponivel);
    if (num_cores) *num_cores = max_cor + 1;
    return cores;
}

// GULOSA
int* coloracao_gulosa(GrafoLista *g, int *num_cores) {
    int n = g->num_vertices;
    int *ordem = (int*) malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) ordem[i] = i;

    int *cores = colorir_por_ordem(g, ordem, num_cores);
    free(ordem);
    return cores;
}

// WELSH-POWELL
typedef struct {
    int vertice;
    int grau;
} NoGrau;

static int comparar_graus(const void *a, const void *b) {
    return ((NoGrau*)b)->grau - ((NoGrau*)a)->grau; // Ordem decrescente
}

// 2. Coloração Welsh-Powell
int* coloracao_welsh_powell(GrafoLista *g, int *num_cores) {
    int n = g->num_vertices;
    NoGrau *nos = (NoGrau*) malloc(n * sizeof(NoGrau));

    for (int i = 0; i < n; i++) {
        nos[i].vertice = i;
        nos[i].grau = 0;
        for (No *p = g->lista_adj[i]; p != NULL; p = p->prox) {
            nos[i].grau++;
        }
    }

    // Ordenar por grau decrescente
    qsort(nos, n, sizeof(NoGrau), comparar_graus);

    int *ordem = (int*) malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        ordem[i] = nos[i].vertice;
    }

    int *cores = colorir_por_ordem(g, ordem, num_cores);

    free(nos);
    free(ordem);
    return cores;
}

// 3. BIPARTIDO (1 se for bipartido, 0 se não for)
int eh_bipartido(GrafoLista *g) {
    int n = g->num_vertices;
    int *cor = (int*) malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) cor[i] = -1;

    int *fila = (int*) malloc(n * sizeof(int));

    for (int inicio = 0; inicio < n; inicio++) {
        if (cor[inicio] != -1) continue;

        cor[inicio] = 1;
        int inicio_f = 0, fim_f = 0;
        fila[fim_f++] = inicio;

        while (inicio_f < fim_f) {
            int u = fila[inicio_f++];

            for (No *p = g->lista_adj[u]; p != NULL; p = p->prox) {
                int v = p->vertice;

                if (cor[v] == -1) {
                    cor[v] = 1 - cor[u]; // Alterna entre 0 e 1
                    fila[fim_f++] = v;
                } else if (cor[v] == cor[u]) {
                    free(cor);
                    free(fila);
                    return 0; // Falso: conflito de cores adjacentes
                }
            }
        }
    }

    free(cor);
    free(fila);
    return 1; // Verdadeiro
}


GrafoLista* criar_grafo(int num_vertices) {
    GrafoLista *g = (GrafoLista*) malloc(sizeof(GrafoLista));
    g->num_vertices = num_vertices;
    g->lista_adj = (No**) calloc(num_vertices, sizeof(No*));
    return g;
}

void adicionar_aresta(GrafoLista *g, int u, int v) {
    No *novo = (No*) malloc(sizeof(No));
    novo->vertice = v;
    novo->prox = g->lista_adj[u];
    g->lista_adj[u] = novo;

    novo = (No*) malloc(sizeof(No));
    novo->vertice = u;
    novo->prox = g->lista_adj[v];
    g->lista_adj[v] = novo;
}

void destruir_grafo(GrafoLista *g) {
    for (int i = 0; i < g->num_vertices; i++) {
        No *p = g->lista_adj[i];
        while (p) {
            No *t = p;
            p = p->prox;
            free(t);
        }
    }
    free(g->lista_adj);
    free(g);
}