#include <stdio.h>
#include <stdlib.h>
#include "grafo_matriz.h"

int main(){
    GrafoMatriz *matriz = criar_grafo_matriz(5);

    if (matriz == NULL) return 1;

    inserir_aresta(matriz, 3, 4);
    inserir_aresta(matriz, 4, 4);
    inserir_aresta(matriz, 1, 3);
    inserir_aresta(matriz, 1, 1);
    exibir_matriz(matriz);
    printf("\n");
    remover_aresta(matriz, 3, 4);
    exibir_matriz(matriz);

    return 0;
}