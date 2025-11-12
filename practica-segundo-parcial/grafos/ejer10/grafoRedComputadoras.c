// Librerias
#include <stdio.h>

// Archivo TAD
#include "grafoRedComputadoras.h"

// Funcion principal
int main(){
    tGrafoRedComputadoras grafo;
    tArista arista;

    arista.origen = 0;
    arista.destino = 1;
    arista.peso.nivelDeLatencia =40;
    arista.peso.velocidadEnlace = 100;
    
    agregarArista(&grafo, arista);
    eliminarArista(&grafo, arista);
    visualizarMatriz(grafo);

    return 0;
}
