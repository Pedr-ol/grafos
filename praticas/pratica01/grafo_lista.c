#include <stdio.h>
#include <stdlib.h>
#include "grafo_lista.h"

GrafoLista criar_grafo_lista(int n) {
    GrafoLista lista;

    lista.n = n;
    lista.adj = NULL;

    lista.adj = calloc(n, sizeof(No *));

    return lista;
}

void inserir_aresta_lista(GrafoLista *lista, int u, int v) {
    No *novo = malloc(sizeof(No));

    if(novo ==NULL){
        return;
    }

    novo->destino = v;
    novo->prox = lista->adj[u];
    lista->adj[u] = novo;
}

void remover_aresta_lista(GrafoLista *lista, int u, int v) {
    No *atual = lista->adj[u];
    No *anterior = NULL;

    while(atual!=NULL){
        if(atual->destino == v){
            if(anterior == NULL){
                lista->adj[u] = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }
            free(atual);
            return;
        }

        anterior = atual;
        atual = atual->prox;
    }
}

int grau_lista(GrafoLista *lista, int u) {
   int grau = 0;
   No *atual = lista->adj[u]; 

   while (atual != NULL) {
        grau++;
        atual = atual->prox;
    }

    return grau;
}
int sao_adjacentes_lista(GrafoLista *lista, int u, int v) {
    No *atual = lista->adj[u];

    while (atual != NULL) {

        if (atual->destino == v) {
            return 1;
        }
        atual = atual->prox;
    }

    return 0;
}

void liberar_grafo_lista(GrafoLista *lista) {
    free(lista->adj);

    lista->adj = NULL;
    lista->n = 0;
}

void exibir_lista(GrafoLista *lista) {
    for (int i = 0; i < lista->n; i++) {

        printf("%d:", i);

        No *atual = lista->adj[i];

        while (atual != NULL) {
            printf(" -> %d", atual->destino);
            atual = atual->prox;
        }

        printf("\n");
    }
}
