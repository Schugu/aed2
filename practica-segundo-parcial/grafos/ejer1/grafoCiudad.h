#ifndef GRAFOCIUDAD_H
#define GRAFOCIUDAD_H

// Librerias
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Constantes
#define MAX 90

// Tipos
typedef struct {
    float distanciaMetros;
    float promedioTrafico;
} tPeso;

typedef int tVertice;

typedef struct {
    tVertice origen;
    tVertice destino;
    tPeso peso;
} tArco;

typedef bool conjuntoVertices[MAX];

typedef tPeso conjuntoArcos[MAX][MAX];

typedef struct {
    conjuntoVertices vertices;
    conjuntoArcos arcos;
    int cantVertices;
} tGrafoCiudad;

// Prototipado
void inicializarGrafo(tGrafoCiudad*);
void agregarVertice(tGrafoCiudad*, tVertice);
void agregarAristas(tGrafoCiudad*, tVertice, tVertice, tPeso);
bool existeArista(tGrafoCiudad, tVertice, tVertice);
int maximoVertice(tGrafoCiudad);
void visualizarMatriz(tGrafoCiudad);

// Funciones
void inicializarGrafo(tGrafoCiudad* pGrafo) {
    pGrafo->cantVertices = 0;
    for (int i = 0; i < MAX; i++) {
        pGrafo->vertices[i] = false;
        for (int j = 0; j < MAX; j++) {
            pGrafo->arcos[i][j].distanciaMetros = 0;
            pGrafo->arcos[i][j].promedioTrafico = 0;
        }
    }
    // printf("Grafo inicializado correctamente\n");
}

void agregarVertice(tGrafoCiudad* pGrafo, tVertice pVertice) {
    if (pVertice >= 0 && pVertice < MAX) {
        if (!pGrafo->vertices[pVertice]) {
            pGrafo->vertices[pVertice] = true;
            pGrafo->cantVertices++;
            printf("Vertice agregado correctamente.\n");
        } else {
            printf("Error: el vertice ya existe.\n");
        }
    } else {
        printf("Error al agregar el vertice.\n");
    }
}

void agregarAristas(tGrafoCiudad* pGrafo, tVertice a, tVertice b, tPeso pPeso) {
    if (pGrafo->vertices[a] && pGrafo->vertices[b]) {
        pGrafo->arcos[a][b].distanciaMetros = pPeso.distanciaMetros;
        pGrafo->arcos[a][b].promedioTrafico = pPeso.promedioTrafico;

        pGrafo->arcos[b][a].distanciaMetros = pPeso.distanciaMetros;
        pGrafo->arcos[b][a].promedioTrafico = pPeso.promedioTrafico;

        printf("Aristas agregadas.\n");
    } else {
        printf("Error al agregar aristas.");
    }
}

bool existeArista(tGrafoCiudad pGrafo, tVertice a, tVertice b) {
    return (pGrafo.arcos[a][b].distanciaMetros != 0.0 ||
            pGrafo.arcos[a][b].promedioTrafico != 0.0) &&
           pGrafo.vertices[a] && pGrafo.vertices[b];
}

int maximoVertice(tGrafoCiudad pGrafo) {
    int max = -1;
    for (int i = 0; i < MAX; i++) {
        if (pGrafo.vertices[i]) {
            max = i;
        }
    }
    return max;
}

void visualizarMatriz(tGrafoCiudad pGrafo) {
    if (pGrafo.cantVertices == 0) {
        printf("El grafo esta vacio (no existen vertices)\n");
        return;
    }

    int maxV = maximoVertice(pGrafo);

    printf("\n========================================\n");
    printf("MATRIZ DE PESOS - Total vertices: %d\n", pGrafo.cantVertices);
    printf("========================================\n\n");

    // Encabezado de columnas
    printf("     ");
    for (int j = 0; j <= maxV; j++) {
        if (pGrafo.vertices[j]) {
            printf("    %-2d           ", j);
        }
    }
    printf("\n");

    // Filas
    for (int i = 0; i <= maxV; i++) { //
        if (!pGrafo.vertices[i]) {
            continue;
        }

        printf("%-2d |", i);

        // Columnas
        for (int j = 0; j <= maxV; j++) {
            if (!pGrafo.vertices[j]) {
                continue;
            }

            if (existeArista(pGrafo, i, j)) {
                printf("(%6.2f |%6.2f) ",
                       pGrafo.arcos[i][j].distanciaMetros,
                       pGrafo.arcos[i][j].promedioTrafico);
            } else {
                printf("      -         ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

#endif