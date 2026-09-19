#include <stdio.h>
#include <stdlib.h>
#include "grafo_matriz.h"
#include "grafo_lista.h"

int main(){
    //MATRIZ
    GrafoMatriz *matriz = criar_grafo_matriz(5);

    if (matriz == NULL) return 1;

    inserir_aresta(matriz, 3, 4);
    inserir_aresta(matriz, 4, 4);
    inserir_aresta(matriz, 1, 3);
    inserir_aresta(matriz, 1, 1);
    printf("\n\nMATRIZ DE ADJACENCIA:\n");
    exibir_matriz(matriz);
    printf("\n");
    remover_aresta(matriz, 3, 4);
    printf("Aresta (3,4) removida!\n");
    exibir_matriz(matriz);
    printf("\n");

    printf("Grau do vertice 1: %d\n", grau_matriz(matriz, 1));

    printf("Os vertices 1 e 3 sao adjacentes? ");
    if (sao_adjacentes_matriz(matriz, 1, 3)) {
    printf("Sim\n");
    } else {
    printf("Não\n");
    }
    
    liberar_grafo(matriz);

    //LISTA
    GrafoLista lista = criar_grafo_lista(5);
    
    inserir_aresta_lista(&lista, 3, 4);
    inserir_aresta_lista(&lista, 4, 4);
    inserir_aresta_lista(&lista, 1, 3);
    inserir_aresta_lista(&lista, 1, 1);
    printf("\nLISTA DE ADJACENCIA:\n");
    exibir_lista(&lista);
    printf("\n");
    remover_aresta_lista(&lista, 3, 4);
    printf("Aresta (3,4) removida!\n");
    exibir_lista(&lista);
    
    printf("\nGrau do vertice 1: %d\n", grau_lista(&lista, 1));
    
    printf("Os vertices 1 e 4 sao adjacentes? ");
    if (sao_adjacentes_lista(&lista, 1, 4)) {
        printf("Sim\n");
    } else {
        printf("Não\n");
    }


    return 0;
}
