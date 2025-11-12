// Librerias
#include <stdio.h>

// Archivo TAD
#include "grafoCiudad.h"

// Funcion principal
int main() {
    tGrafoCiudad grafo;

    tArista arista;
    arista.origen = 0;
    arista.destino = 1;
    arista.peso.distanciaMetros = 100;
    arista.peso.proemdioTrafico = 30;

    agregarAristas(&grafo, arista);

    visualizarMatriz(grafo);

    return 0;
}