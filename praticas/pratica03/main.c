#include <stdio.h>
#include "dag.h"

void imprimir(const char* label, int *arr, int tam) {
    printf("%-6s ", label);
    if (!arr) { 
        printf("NULL (Contem ciclo!)\n"); 
        return; 
    }
    for (int i = 0; i < tam; i++) printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    // -------------------------------------------------------------
    // TESTE 1: DAG em formato de diamante (5 vertices)
    // Fluxo: 0 -> 1 -> 3
    //        0 -> 2 -> 3 -> 4
    // -------------------------------------------------------------
    printf("=== TESTE 1: DAG (Sem ciclos) ===\n");
    GrafoLista* g1 = criar_grafo(5);
    adicionar_aresta(g1, 0, 1);
    adicionar_aresta(g1, 0, 2);
    adicionar_aresta(g1, 1, 3);
    adicionar_aresta(g1, 2, 3);
    adicionar_aresta(g1, 3, 4);

    printf("Eh DAG? %s\n", eh_dag(g1) ? "Sim" : "Nao");

    int tam_dfs1, tam_kahn1;
    int *dfs1 = ordenacao_topologica_dfs(g1, &tam_dfs1);
    int *kahn1 = ordenacao_topologica_kahn(g1, &tam_kahn1);

    imprimir("DFS:", dfs1, tam_dfs1);
    imprimir("Kahn:", kahn1, tam_kahn1);

    // -------------------------------------------------------------
    // TESTE 2: Grafo com ciclo (3 vertices)
    // Ciclo: 0 -> 1 -> 2 -> 0
    // -------------------------------------------------------------
    printf("\n=== TESTE 2: Grafo com Ciclo ===\n");
    GrafoLista* g2 = criar_grafo(3);
    adicionar_aresta(g2, 0, 1);
    adicionar_aresta(g2, 1, 2);
    adicionar_aresta(g2, 2, 0); // Fecha o ciclo de volta para o 0

    printf("Eh DAG? %s\n", eh_dag(g2) ? "Sim" : "Nao");

    int tam_dfs2, tam_kahn2;
    int *dfs2 = ordenacao_topologica_dfs(g2, &tam_dfs2);
    int *kahn2 = ordenacao_topologica_kahn(g2, &tam_kahn2);

    imprimir("DFS:", dfs2, tam_dfs2);
    imprimir("Kahn:", kahn2, tam_kahn2);

    return 0;
}