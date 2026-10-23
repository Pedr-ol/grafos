
#include "grafo_lista.h"

#ifndef ORDENACAO_TOPOLOGICA
#define ORDENACAO_TOPOLOGICA

void ordenar_dfs(GrafoLista *g, int u, int *visitado, int *idx, int *ordenacao);
void buscar_dfs(GrafoLista *g, int u, int *visitado, int *idx, int *ordenacao);

#endif