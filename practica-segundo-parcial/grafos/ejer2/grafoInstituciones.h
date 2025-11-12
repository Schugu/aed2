#ifndef GRAFOSINSTITUCIONES_H
#define GRAFOSINSTITUCIONES_H

// Librerias
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Constantes
#define MAX 150

// Tipos
typedef struct {
    float distancia;
    float promedioEstudiantes;
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
} tGrafoInstituciones;

// Prototipado
void inicializarGrafo(tGrafoInstituciones*);
void agregarVertice(tGrafoInstituciones*, tVertice);
void eliminarVertice(tGrafoInstituciones*, tVertice);

// Funcioens
void inicializarGrafo(tGrafoInstituciones* pGrafo) {
    pGrafo->cantVertices = 0;
    for (int i = 0; i < MAX; i++) {
        pGrafo->vertices[i] = false;
        for (int j = 0; j < MAX; j++) {
            pGrafo->arcos[i][j].distancia = 0;
            pGrafo->arcos[i][j].promedioEstudiantes = 0;
        }
    }
}

void agregarVertice(tGrafoInstituciones* pGrafo, tVertice pVertice) {
    if (pVertice >= 0 && pVertice < MAX) {
        if (!pGrafo->vertices[pVertice]) {
            pGrafo->vertices[pVertice] = true;
            pGrafo->cantVertices++;
            printf("Vertice agregado correctamente.\n");
        } else {
            printf("Error: ya existe el vertice.\n");
        }
    } else {
        printf("Errro: vertice invalido.\n");
    }
}

void eliminarVertice(tGrafoInstituciones* pGrafo, tVertice pVertice) {
    if (pGrafo->vertices[pVertice]) {
        pGrafo->vertices[pVertice] = false;
        pGrafo->cantVertices--;

        // Limpiar Aristas
        for (int i = 0; i < MAX; i++) {
            pGrafo->arcos[pVertice][i].distancia = 0;
            pGrafo->arcos[pVertice][i].promedioEstudiantes = 0;
            pGrafo->arcos[i][pVertice].distancia = 0;
            pGrafo->arcos[i][pVertice].promedioEstudiantes = 0;
        }

        printf("Vertice eliminado.\n");
    } else {
        printf("El vertice no existe.\n");
    }
}

#endif