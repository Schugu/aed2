// Librerias
#include <stdio.h>

// Archivo TAD
#include "grafoRedSocial.h"

// Funcion principal
int main() {
    tGrafoRedSocial grafo;
    inicializarGrafo(&grafo);

    agregarVertice(&grafo, 0);
    agregarVertice(&grafo, 1);

    tArco arco;
    arco.origen = 0;
    arco.destino = 1;
    arco.peso.intensidad = 200;
    strcpy(arco.peso.fechaPrimeraInteraccion, "11-11-2025");
    agregarArco(&grafo, arco);

    return 0;
}