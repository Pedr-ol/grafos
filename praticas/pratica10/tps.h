#ifndef TPS_H
#define TPS_H

void grafo_para_tsp(int n, int grafo[15][15], int pesos[15][15]);
int tsp_forca_bruta(int n, int pesos[15][15], int melhor_caminho[]);
int tsp_vizinho_mais_proximo(int n, int pesos[15][15], int caminho[]);
int tsp_insercao(int n, int pesos[15][15], int caminho[]);

#endif
