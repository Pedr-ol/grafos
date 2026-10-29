#include <stdio.h>
#include <stdlib.h>
#include "agm.h"

#define INF 999999

/* ---------- DSU ---------- */

int find(DSU *d, int x) {
    if (d->pai[x] != x) {
        d->pai[x] = find(d, d->pai[x]);
    }

    return d->pai[x];
}

void unir(DSU *d, int x, int y) {
    int rx = find(d, x);
    int ry = find(d, y);

    if (rx == ry) {
        return;
    }

    if (d->rank[rx] < d->rank[ry]) {
        d->pai[rx] = ry;
    } else if (d->rank[rx] > d->rank[ry]) {
        d->pai[ry] = rx;
    } else {
        d->pai[ry] = rx;
        d->rank[rx]++;
    }
}

/* ---------- KRUSKAL ---------- */

int comparar_arestas(const void *a, const void *b) {
    const Aresta *x = a;
    const Aresta *y = b;

    return (x->peso > y->peso) - (x->peso < y->peso);
}

int kruskal(int V, Aresta arestas[], int E, Aresta resultado[]) {
    Aresta *ordenadas = malloc(E * sizeof(Aresta));
    DSU d;

    d.n = V;
    d.pai = malloc(V * sizeof(int));
    d.rank = calloc(V, sizeof(int));

    for (int i = 0; i < E; i++) {
        ordenadas[i] = arestas[i];
    }

    qsort(ordenadas, E, sizeof(Aresta), comparar_arestas);

    for (int i = 0; i < V; i++) {
        d.pai[i] = i;
    }

    int qtd = 0;

    for (int i = 0; i < E && qtd < V - 1; i++) {
        int u = ordenadas[i].u;
        int v = ordenadas[i].v;

        if (find(&d, u) != find(&d, v)) {
            resultado[qtd++] = ordenadas[i];
            unir(&d, u, v);
        }
    }

    free(ordenadas);
    free(d.pai);
    free(d.rank);

    return qtd;
}

/* ---------- HEAP MINIMO PARA PRIM ---------- */

typedef struct {
    int vertice;
    int chave;
} ItemHeap;

typedef struct {
    ItemHeap *itens;
    int *pos;
    int tamanho;
} Heap;

void trocar(Heap *h, int i, int j) {
    ItemHeap temp = h->itens[i];
    h->itens[i] = h->itens[j];
    h->itens[j] = temp;

    h->pos[h->itens[i].vertice] = i;
    h->pos[h->itens[j].vertice] = j;
}

void subir(Heap *h, int i) {
    while (i > 0) {
        int pai = (i - 1) / 2;

        if (h->itens[pai].chave <= h->itens[i].chave) {
            break;
        }

        trocar(h, pai, i);
        i = pai;
    }
}

void descer(Heap *h, int i) {
    while (1) {
        int menor = i;
        int esq = 2 * i + 1;
        int dir = 2 * i + 2;

        if (esq < h->tamanho &&
            h->itens[esq].chave < h->itens[menor].chave) {
            menor = esq;
        }

        if (dir < h->tamanho &&
            h->itens[dir].chave < h->itens[menor].chave) {
            menor = dir;
        }

        if (menor == i) {
            break;
        }

        trocar(h, i, menor);
        i = menor;
    }
}

ItemHeap extrair_minimo(Heap *h) {
    ItemHeap minimo = h->itens[0];

    h->pos[minimo.vertice] = -1;
    h->tamanho--;

    if (h->tamanho > 0) {
        h->itens[0] = h->itens[h->tamanho];
        h->pos[h->itens[0].vertice] = 0;
        descer(h, 0);
    }

    return minimo;
}

void diminuir_chave(Heap *h, int v, int nova_chave) {
    int i = h->pos[v];

    if (i == -1 || nova_chave >= h->itens[i].chave) {
        return;
    }

    h->itens[i].chave = nova_chave;
    subir(h, i);
}

/* ---------- PRIM ---------- */

int prim(int V, Aresta arestas[], int E, Aresta resultado[]) {
    No **lista = calloc(V, sizeof(No *));
    int *pai = malloc(V * sizeof(int));
    int *chave = malloc(V * sizeof(int));

    for (int i = 0; i < E; i++) {
        int u = arestas[i].u;
        int v = arestas[i].v;
        int peso = arestas[i].peso;

        No *novo = malloc(sizeof(No));
        novo->vertice = v;
        novo->peso = peso;
        novo->prox = lista[u];
        lista[u] = novo;

        novo = malloc(sizeof(No));
        novo->vertice = u;
        novo->peso = peso;
        novo->prox = lista[v];
        lista[v] = novo;
    }

    Heap h;
    h.itens = malloc(V * sizeof(ItemHeap));
    h.pos = malloc(V * sizeof(int));
    h.tamanho = V;

    for (int i = 0; i < V; i++) {
        pai[i] = -1;
        chave[i] = INF;

        h.itens[i].vertice = i;
        h.itens[i].chave = INF;
        h.pos[i] = i;
    }

    /* Começa pelo vértice A (índice 0). */
    chave[0] = 0;
    h.itens[0].chave = 0;
    subir(&h, 0);

    int qtd = 0;

    while (h.tamanho > 0) {
        ItemHeap item = extrair_minimo(&h);
        int u = item.vertice;

        if (pai[u] != -1) {
            resultado[qtd].u = pai[u];
            resultado[qtd].v = u;
            resultado[qtd].peso = chave[u];
            qtd++;
        }

        No *atual = lista[u];

        while (atual != NULL) {
            int v = atual->vertice;
            int peso = atual->peso;

            if (h.pos[v] != -1 && peso < chave[v]) {
                pai[v] = u;
                chave[v] = peso;
                diminuir_chave(&h, v, peso);
            }

            atual = atual->prox;
        }
    }

    for (int i = 0; i < V; i++) {
        No *atual = lista[i];

        while (atual != NULL) {
            No *temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }

    free(lista);
    free(pai);
    free(chave);
    free(h.itens);
    free(h.pos);

    return qtd;
}
