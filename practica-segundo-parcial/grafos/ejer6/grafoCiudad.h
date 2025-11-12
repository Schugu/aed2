#ifndef GRAFOCIUDAD_H
#define GRAFOCIUDAD_H

// Librerias
#include <stdio.h>
#include <stdbool.h>

// Constantes
#define MAX 90

// Tipos
typedef struct {
    float distanciaMetros;
    float proemdioTrafico;
} tPeso;

typedef int tVertice;

typedef struct {
    tVertice origen;
    tVertice destino;
    tPeso peso;
} tArista;

typedef bool conjuntoVertices[MAX];

typedef tArista conjuntoAristas[MAX][MAX];

typedef struct {
    conjuntoVertices vertices;
    conjuntoAristas aristas;
    int cantVertices;
} tGrafoCiudad;

// Prototipado
void agregarAristas(tGrafoCiudad*, tArista);
bool existeVertice(tGrafoCiudad, tVertice);
bool exiteArista(tGrafoCiudad, tVertice, tVertice);
void visualizarMatriz(tGrafoCiudad);

// Funciones
void agregarAristas(tGrafoCiudad* pGrafo, tArista pArista) {
    if (pGrafo->vertices[pArista.origen] == true &&
        pGrafo->vertices[pArista.destino] == true) {

        pGrafo->aristas[pArista.origen][pArista.destino].peso.distanciaMetros = pArista.peso.distanciaMetros;
        pGrafo->aristas[pArista.origen][pArista.destino].peso.proemdioTrafico = pArista.peso.proemdioTrafico;

        pGrafo->aristas[pArista.destino][pArista.origen].peso.distanciaMetros = pArista.peso.distanciaMetros;
        pGrafo->aristas[pArista.destino][pArista.origen].peso.proemdioTrafico = pArista.peso.proemdioTrafico;

        printf("Arista agregada.\n");
    } else {
        printf("Error al agregar la arista. \n");
    }
}

bool existeVertice(tGrafoCiudad pGrafo, tVertice pVertice) {
    return pVertice >= 0 && pVertice < MAX && pGrafo.vertices[pVertice] == true;
}

bool exiteArista(tGrafoCiudad pGrafo, tVertice origen, tVertice destino) {
    return (existeVertice(pGrafo, origen) &&
            existeVertice(pGrafo, destino) &&
            (pGrafo.aristas[origen][destino].peso.distanciaMetros != 0.0 ||
             pGrafo.aristas[origen][destino].peso.proemdioTrafico != 0.0));
}

void visualizarMatriz(tGrafoCiudad pGrafo) {
    if (!pGrafo.cantVertices) {
        printf("Error: no hay vertices");
        return;
    }

    // Imprimir cabecera
    printf("--- Matriz de adyacencia --- \n");
    printf("   ");
    for (int i = 0; i < pGrafo.cantVertices; i++) {
        printf("%7d", i);
    }
    printf("\n");

    // Imprimir linea separadora
    printf("   ");
    for (int i = 0; i < pGrafo.cantVertices; i++) {
        printf("----");
    }
    printf("\n");

    // Imprimir matriz
    for (int i = 0; i < pGrafo.cantVertices; i++) {
        // Imprimir Lineas
        printf("%3d| ", i);
        for (int j = 0; j < pGrafo.cantVertices; j++) {
            if (exiteArista(pGrafo, i, j)) {
                printf("%6.0f - %6.0f ",
                       pGrafo.aristas[i][j].peso.distanciaMetros,
                       pGrafo.aristas[i][j].peso.proemdioTrafico);
            } else {
                printf("   ---   ");
            }
        }
        printf("\n");
    }
}

#endif