#include "hamiltoniano.h"

int encontrar_caminho_hamiltoniano_bt(
    int n,
    int grafo[15][15],
    int caminho[],
    int visitado[],
    int pos
) {
    if (pos == n) {
        return 1;
    }

    for (int v = 0; v < n; v++) {
        if (!visitado[v]) {
            if (pos == 0 || grafo[caminho[pos - 1]][v]) {
                caminho[pos] = v;
                visitado[v] = 1;

                if (encontrar_caminho_hamiltoniano_bt(n, grafo, caminho, visitado, pos + 1)) {
                    return 1;
                }

                visitado[v] = 0;
            }
        }
    }

    return 0;
}
