#include "planaridade.h"

int eh_planar_euler(GrafoLista *g) {
    // Grafos com menos de 3 vértices são sempre planares.
    // Para n >= 3, a condição necessária de Euler é m <= 3n - 6.
    return (g->n < 3) || (g->m <= 3 * g->n - 6);
}