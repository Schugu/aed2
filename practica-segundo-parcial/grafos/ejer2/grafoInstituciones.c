// Librerias
#include <stdio.h>

// Archivo TAD
#include "grafoInstituciones.h"

// Funcion principal
int main() {
    tGrafoInstituciones grafo;

    inicializarGrafo(&grafo);

    agregarVertice(&grafo, 0);

    eliminarVertice(&grafo, 0);

    return 0;
}