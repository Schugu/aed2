// Librerias
#include <stdio.h>

// Archivo TAD
#include "grafoHospital.h"

// Funcion general
int main(){
    tGrafoHospital grafo;
    tArista arista;

    arista.origen = 0;
    arista.destino = 1;
    arista.peso.distanciaMetros =100;
    arista.peso.tiempoPromedio = 20;

    agregarArista(&grafo, arista);

    visualizarMatriz(grafo);

    return 0;
}