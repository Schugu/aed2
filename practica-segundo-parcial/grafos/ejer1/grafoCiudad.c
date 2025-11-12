// Librerias
#include <stdio.h>

// Archivo TAD
#include "grafoCiudad.h"

// Funcion principal
int main() {
    tGrafoCiudad grafo;

    inicializarGrafo(&grafo);

    agregarVertice(&grafo, 0);
    agregarVertice(&grafo, 1);
    agregarVertice(&grafo, 2);

    tPeso peso;

    peso.distanciaMetros = 200;
    peso.promedioTrafico = 30;
    agregarAristas(&grafo, 0, 1, peso);

    peso.distanciaMetros = 200;
    peso.promedioTrafico = 30;
    agregarAristas(&grafo, 1, 2, peso);

    peso.distanciaMetros = 200;
    peso.promedioTrafico = 30;
    agregarAristas(&grafo, 2, 0, peso);

    visualizarMatriz(grafo);
}
