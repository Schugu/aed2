// Librerias
#include <stdio.h>

// Archivo TAD
#include "grafoTransporte.h"

// Funcion principal
int main (){
    tGrafoTransporte grafo;
    tArista arista;

    arista.origen= 0;
    arista.destino = 1;
    arista.peso.distanciaKilom = 10;
    arista.peso.tiempoPromedio = 100;

    agregarArista(&grafo, arista);

    eliminarArista(&grafo, arista);

    visualizarMatriz(grafo);

    return 0;
}