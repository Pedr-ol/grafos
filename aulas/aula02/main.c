#include <stdio.h>
#include "grafo_matriz.h"

int main() {

    GrafoMatriz grafo;

    inicializar(&grafo, 8);

    inserir_aresta(&grafo, 0, 1);
    inserir_aresta(&grafo, 0, 2);
    inserir_aresta(&grafo, 0, 3);
    inserir_aresta(&grafo, 1, 4);
    inserir_aresta(&grafo, 1, 5);
    inserir_aresta(&grafo, 2, 3);
    inserir_aresta(&grafo, 2, 6);
    inserir_aresta(&grafo, 3, 6);
    inserir_aresta(&grafo, 7, 4);
    inserir_aresta(&grafo, 7, 5);
    inserir_aresta(&grafo, 7, 6);

    printf("\nMATRIZ DE ADJACENCIA - Nao orientado\n");
    exibir_matriz(&grafo);


    inicializar(&grafo, 8);
    printf("\nMATRIZ DE ADJACENCIA - Orientado\n");


    inserir_arco(&grafo, 0, 1);
    inserir_arco(&grafo, 0, 2);
    inserir_arco(&grafo, 0, 3);
    inserir_arco(&grafo, 1, 4);
    inserir_arco(&grafo, 1, 5);
    inserir_arco(&grafo, 2, 3);
    inserir_arco(&grafo, 2, 6);
    inserir_arco(&grafo, 3, 6);
    inserir_arco(&grafo, 7, 4);
    inserir_arco(&grafo, 7, 5);
    inserir_arco(&grafo, 7, 6);
    
    exibir_matriz(&grafo);
    return 0;
}